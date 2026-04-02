#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

/**
 * Copy data to pOutput to play sound (buffer read by sound card)
 * PCM frame = frame = sample * #channels (in miniaudio)
 */
void data_callback(ma_device* device, void* output, [[ maybe_unused ]] const void* input, ma_uint32 n_frames_to_process) {
  ma_decoder* decoder = (ma_decoder*) device->pUserData;
  ma_uint64 n_frames_read;
  ma_decoder_read_pcm_frames(decoder, output, n_frames_to_process, &n_frames_read);

  std::cout << "# frames to process: " << n_frames_to_process
            << " # frames read: " << n_frames_read << '\n';
}

/* See miniaudio/examples/simple_playback.c */
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

  // device stopped after init (=> begin playback)
  result = ma_device_start(&device);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to start playback - result: " << result << '\n';
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  // audio played in the background audio thread => program must live long enough!
  printf("Press Enter to quit...");
  getchar();

  ma_device_uninit(&device);
  ma_decoder_uninit(&decoder);

  return 0;
}
