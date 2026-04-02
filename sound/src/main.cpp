#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

static ma_pcm_rb ring_buffer;

/**
 * PCM frame = frame = sample * #channels (in miniaudio)
 */
void data_callback(ma_device* device, void* output, [[ maybe_unused ]] const void* input, ma_uint32 n_frames) {
  /* Copy data to pOutput to play sound (buffer read by sound card) */
  ma_decoder* decoder = (ma_decoder*) device->pUserData;
  ma_uint64 n_frames_decoded;
  ma_decoder_read_pcm_frames(decoder, output, n_frames, &n_frames_decoded);
  std::cout << " # frames decoded: " << n_frames_decoded << '\n';

  ma_format format = decoder->outputFormat;
  ma_uint32 n_channels = decoder->outputChannels;

  /* Write frames to ring buffer */
  ma_uint32 n_frames_written = 0;

  while (n_frames_written < n_frames_decoded) {
    ma_result result;

    // retrieve a pointer to a section of the ring buffer
    // #frames returned could be != #frames requested (e.g. clamped if #frames requested require a loop in rb) => use a loop
    void* section_rb;
    ma_uint32 n_frames_to_write = n_frames_decoded - n_frames_written;
    result = ma_pcm_rb_acquire_write(&ring_buffer, &n_frames_to_write, &section_rb);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to acquire rb lock - result: " << result << '\n';
      return;
    }

    if (n_frames_to_write == 0)
      break;

    // copy frames to the ring buffer
    const float* ptr_buffer_src = ma_offset_pcm_frames_const_ptr_f32((const float*) output, n_frames_written, n_channels);
    ma_copy_pcm_frames(section_rb, ptr_buffer_src, n_frames_to_write, format, n_channels);

    // update ring buffer's interior pointers
    result = ma_pcm_rb_commit_write(&ring_buffer, n_frames_to_write);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to commit writing - result: " << result << '\n';
      return;
    }

    n_frames_written += n_frames_to_write;
    std::cout << " # frames written: " << n_frames_to_write << '\n';
  } // END WHILE
}

/**
 * Ring buffer appropriate for the case of one producer (decoder) & one consumer (UI)
 * See miniaudio/examples/simple_playback.c & miniaudio/examples/hilo_interop.c
 */
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << " SOUND" << '\n';
    return 0;
  }

  ma_result result;

  // decoder (to read audio file)
  ma_decoder decoder;
  result = ma_decoder_init_file(argv[1], NULL, &decoder);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to decode audio file - result: " << result << '\n';
    return 1;
  }

  // config (send decoder via device to retrieve frames from it in callback)
  ma_device_config config = ma_device_config_init(ma_device_type_playback);
  config.playback.format = decoder.outputFormat;
  config.playback.channels = decoder.outputChannels;
  config.sampleRate = decoder.outputSampleRate;
  config.dataCallback = data_callback;
  config.pUserData = &decoder;

  // device
  ma_device device;
  result = ma_device_init(NULL, &config, &device);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to init device - result: " << result << '\n';
    ma_decoder_uninit(&decoder);
    return 1;
  }

  // ring buffer
  // period: # of audio frames (chunk) processed each time
  // 5 * periods: tolerance to avoid latency due to dropouts
  result = ma_pcm_rb_init(device.playback.format, device.playback.channels, 5 * device.playback.internalPeriodSizeInFrames, NULL, NULL, &ring_buffer);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to init ring buffer - result: " << result << '\n';
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  // device stopped after init (=> begin playback)
  result = ma_device_start(&device);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to start playback - result: " << result << '\n';
    ma_pcm_rb_uninit(&ring_buffer);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  // read from ring buffer

  // audio played in the background audio thread => program must live long enough!
  printf("Press Enter to quit...");
  getchar();

  ma_pcm_rb_uninit(&ring_buffer);
  ma_device_uninit(&device);
  ma_decoder_uninit(&decoder);

  return 0;
}
