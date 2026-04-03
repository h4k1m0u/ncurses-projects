#include <iostream>
#include <fstream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

static ma_pcm_rb ring_buffer;

// used to synchronize consumer (UI in main thread) with producer (audio callback)
static ma_event notification;

int calls = 0;

/* Copy `n_frames` frames from `src` to ring buffer */
static void write_to_ring_buffer(void* src, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels) {
  ma_uint32 n_frames_written = 0;

  while (n_frames_written < n_frames) {
    ma_result result;

    // retrieve a pointer to a section of the ring buffer
    // #frames returned could be != #frames requested (e.g. clamped if #frames requested require a loop in rb) => use a loop
    void* section_rb;
    ma_uint32 n_frames_to_write = n_frames - n_frames_written;
    result = ma_pcm_rb_acquire_write(&ring_buffer, &n_frames_to_write, &section_rb);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to acquire write rb lock - result: " << result << std::endl;
      return;
    }

    if (n_frames_to_write == 0)
      break;

    // copy frames to the ring buffer
    const float* ptr_buffer_src = ma_offset_pcm_frames_const_ptr_f32((const float*) src, n_frames_written, n_channels);
    ma_copy_pcm_frames(section_rb, ptr_buffer_src, n_frames_to_write, format, n_channels);

    // update ring buffer's interior pointers
    result = ma_pcm_rb_commit_write(&ring_buffer, n_frames_to_write);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to commit writing - result: " << result << std::endl;
      return;
    }

    n_frames_written += n_frames_to_write;
    std::cout << "# frames written on rb: " << n_frames_to_write << std::endl;
  } // END WHILE
}

/* Read `n_frames` frames from ring buffer into `dst` */
static void read_from_ring_buffer(void* dst, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels) {
  ma_uint32 n_frames_read = 0;

  while (n_frames_read < n_frames) {
    ma_result result;

    // retrieve a pointer to a section of the ring buffer
    // #frames returned could be != #frames requested (e.g. clamped if #frames requested require a loop in rb) => use a loop
    void* section_rb;
    ma_uint32 n_frames_to_read = n_frames - n_frames_read;
    result = ma_pcm_rb_acquire_read(&ring_buffer, &n_frames_to_read, &section_rb);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to acquire read rb lock - result: " << result << std::endl;
      return;
    }

    if (n_frames_to_read == 0)
      break;

    // copy frames to the ring buffer
    float* ptr_buffer_dst = ma_offset_pcm_frames_ptr_f32((float *) dst, n_frames_read, n_channels);
    ma_copy_pcm_frames(ptr_buffer_dst, section_rb, n_frames_to_read, format, n_channels);

    // update ring buffer's interior pointers
    result = ma_pcm_rb_commit_read(&ring_buffer, n_frames_to_read);

    if (result != MA_SUCCESS) {
      std::cout << "Failed to commit reading - result: " << result << std::endl;
      return;
    }

    n_frames_read += n_frames_to_read;
    std::cout << "# frames read from rb: " << n_frames_to_read << std::endl;
  } // END WHILE
}

/**
 * PCM frame = frame = sample * #channels (in miniaudio)
 */
void data_callback(ma_device* device, void* output, [[ maybe_unused ]] const void* input, ma_uint32 n_frames) {
  /* Copy data to pOutput to play sound (buffer read by sound card) */
  ma_decoder* decoder = (ma_decoder*) device->pUserData;
  ma_uint64 n_frames_decoded;
  ma_decoder_read_pcm_frames(decoder, output, n_frames, &n_frames_decoded);

  std::cout << "- # frames decoded (audio callback): " << n_frames_decoded << " call: " << ++calls << std::endl;

  // all audio frames were read
  // TODO: signal event to main loop as we cannot stop inside audio callback (see <miniaudio>/examples/simple_mixing.c)
  if (n_frames_decoded == 0)
    return;

  ////
  /*
  // played frames (decoded from file) from mono sound (1 frame = 1 sample)
  // Note: same values as in audio/a4-1s.txt
  for (ma_uint64 i = 0; i < n_frames_decoded; i++) {
    const float* sample = (float *) output + i;
    f << *sample << '\n';
  }
  */
  ////

  /* Write frames to ring buffer */
  ma_format format = decoder->outputFormat;
  ma_uint32 n_channels = decoder->outputChannels;
  write_to_ring_buffer(output, n_frames_decoded, format, n_channels);

  // notify main thread that data was written to ring buffer (see <miniaudio>/examples/simple_mixing.c)
  ma_event_signal(&notification);
}

/**
 * Ring buffer appropriate for the case of one producer (decoder) & one consumer (UI)
 * See <miniaudio>/examples/simple_playback.c & <miniaudio>/examples/hilo_interop.c
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

  ma_format format = decoder.outputFormat;
  ma_uint32 n_channels = decoder.outputChannels;

  // config (send decoder via device to retrieve frames from it in callback)
  ma_device_config config = ma_device_config_init(ma_device_type_playback);
  config.playback.format = format;
  config.playback.channels = n_channels;
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
  // period: # of audio frames (chunk) processed each time (i.e. n_frames arg. in audio callback)
  // 5 * periods: tolerance to avoid latency due to dropouts
  result = ma_pcm_rb_init(device.playback.format, device.playback.channels, 5 * device.playback.internalPeriodSizeInFrames, NULL, NULL, &ring_buffer);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to init ring buffer - result: " << result << '\n';
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  ma_event_init(&notification);


  // device stopped after init (=> begin playback)
  result = ma_device_start(&device);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to start playback - result: " << result << '\n';
    ma_pcm_rb_uninit(&ring_buffer);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  ////
  // read from ring buffer (see <miniaudio>/examples/simple_mixing.c)
  std::ofstream f("/tmp/sound.txt");

  while (true) {
    ma_event_wait(&notification);

    ma_uint32 n_frames_available = ma_pcm_rb_available_read(&ring_buffer);
    std::cout << "# frames available (main thread): " << n_frames_available << std::endl;

    float* buffer = (float *) malloc(n_frames_available * sizeof(float));
    read_from_ring_buffer(buffer, n_frames_available, format, n_channels);

    // /*
    // frames (read from ring buffer) from mono sound (1 frame = 1 sample)
    // Note: same values as in audio/a4-1s.txt
    for (ma_uint64 i = 0; i < n_frames_available; i++) {
      // std::cout << "Writing frame: " << i << " sample: " << buffer[i] << '\n';
      f << buffer[i] << std::endl;
    }
    // */

    free(buffer);
  }
  ////


  // TODO: signal event from audio callback to stop device (when stream has all been read)

  // audio played in the background audio thread => program must live long enough!
  // printf("Press Enter to quit...");
  getchar();

  ma_event_uninit(&notification);
  ma_pcm_rb_uninit(&ring_buffer);
  ma_device_uninit(&device);
  ma_decoder_uninit(&decoder);

  return 0;
}
