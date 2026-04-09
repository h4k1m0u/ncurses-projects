#include <iostream>
#include <fstream>

#include <ncurses-utils/ncurses_utils.hpp>

#include "ring_buffer.hpp"

static ma_pcm_rb ring_buffer;

// used to synchronize consumer (UI in main thread) with producer (audio callback)
static ma_event notification;

int calls = 0;

/**
 * PCM frame = frame = sample * #channels (in miniaudio)
 */
void data_callback(ma_device* device, void* output, [[ maybe_unused ]] const void* input, ma_uint32 n_frames) {
  /* Copy data to pOutput to play sound (buffer read by sound card) */
  ma_decoder* decoder = (ma_decoder*) device->pUserData;
  ma_uint64 n_frames_decoded;
  ma_decoder_read_pcm_frames(decoder, output, n_frames, &n_frames_decoded);

  // std::cout << "- # frames decoded (audio callback): " << n_frames_decoded << " call: " << ++calls << std::endl;

  // all audio frames were read
  // TODO: signal event to main loop as we cannot stop inside audio callback (see <miniaudio>/examples/simple_mixing.c)
  if (n_frames_decoded == 0)
    return;

  /* Write frames to ring buffer */
  ma_format format = decoder->outputFormat;
  ma_uint32 n_channels = decoder->outputChannels;
  RingBuffer::write(output, ring_buffer, n_frames_decoded, format, n_channels);

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

  const char* path_sound = argv[1];


  //////////////////////////////////////////////////
  // Read sound file
  //////////////////////////////////////////////////

  ma_result result;

  // decoder (to read audio file)
  ma_decoder decoder;
  result = ma_decoder_init_file(path_sound, NULL, &decoder);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to decode audio file - result: " << result << '\n';
    return 1;
  }

  ma_format format = decoder.outputFormat;
  ma_uint32 n_channels = decoder.outputChannels;
  std::cout << "format: " << format << std::endl;
  std::cout << "n_channels: " << n_channels << std::endl;

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

  // notification used to communicate between audio & main thread
  ma_event_init(&notification);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to init notification - result: " << result << '\n';
    ma_pcm_rb_uninit(&ring_buffer);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }

  // device stopped after init (=> begin playback)
  result = ma_device_start(&device);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to start playback - result: " << result << '\n';
    ma_event_uninit(&notification);
    ma_pcm_rb_uninit(&ring_buffer);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    return 1;
  }


  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();
  WINDOW* window = newwin(rows, cols, 0, 0);
  NcursesUtils::configure_input(window);
  std::cout << "rows: " << rows << std::endl;
  std::cout << "cols: " << cols << std::endl;


  //////////////////////////////////////////////////
  // Main loop
  //////////////////////////////////////////////////

  ////
  // read from ring buffer (see <miniaudio>/examples/simple_mixing.c)
  // in stereo 1 frame has 2 samples (i.e. 2 floats)
  std::ofstream f("/tmp/sound.txt");

  while (true) {
    ma_event_wait(&notification);

    ma_uint32 n_frames_available = ma_pcm_rb_available_read(&ring_buffer);
    // std::cout << "# frames available (main thread): " << n_frames_available << std::endl;

    float* buffer = (float *) malloc(n_frames_available * n_channels * sizeof(float));
    RingBuffer::read(buffer, ring_buffer, n_frames_available, format, n_channels);

    // /*
    // frames (read from ring buffer) from mono sound (1 frame = 1 sample)
    // Note: same values as in audio/a4-1s.txt
    for (ma_uint64 i = 0; i < n_frames_available * n_channels; i++) {
      // std::cout << "Writing frame: " << i << " sample: " << buffer[i] << '\n';
      f << buffer[i] << std::endl;
    }
    // */

    // draw bars
    // TODO: use Conversion

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

  delwin(window);
  endwin();

  return 0;
}
