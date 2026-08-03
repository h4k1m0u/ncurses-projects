#include <iostream>
#include <vector>

#include <ncurses-utils/ncurses_utils.hpp>

#include "ring_buffer.hpp"
#include "drawer_bars.hpp"

static ma_pcm_rb ring_buffer;

// used to synchronize consumer (UI in main thread) with producer (audio callback) when samples are available to read
// & also to notify main thread when all audio frames have been read (i.e. EOF reached)
static ma_event notification;

/**
 * PCM frame = frame = sample * #channels (in miniaudio)
 */
void data_callback(ma_device* device, void* output, [[ maybe_unused ]] const void* input, ma_uint32 n_frames) {
  /* Copy data to pOutput to play sound (buffer read by sound card) */
  ma_decoder* decoder = (ma_decoder*) device->pUserData;
  ma_uint64 n_frames_decoded;
  ma_decoder_read_pcm_frames(decoder, output, n_frames, &n_frames_decoded);

  // all audio frames were read
  if (n_frames_decoded == 0) {
    ma_event_signal(&notification);
    return;
  }

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
  // Read sound file & init miniaudio objects
  //////////////////////////////////////////////////

  // decoder (to read audio file)
  ma_result result;
  ma_decoder decoder;
  result = ma_decoder_init_file(path_sound, NULL, &decoder);

  if (result != MA_SUCCESS) {
    std::cout << "Failed to decode audio file - result: " << result << '\n';
    return 1;
  }

  ma_format format = decoder.outputFormat;
  ma_uint32 n_channels = decoder.outputChannels;

  // config (send decoder via device to retrieve frames from it in callback)
  ma_device_config config = ma_device_config_init(ma_device_type_playback);
  config.playback.format = decoder.outputFormat;
  config.playback.channels = decoder.outputChannels;
  config.sampleRate = decoder.outputSampleRate;
  config.dataCallback = data_callback;
  config.pUserData = &decoder;

  // init device (i.e. audio card)
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
  result = ma_event_init(&notification);

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

  std::pair<int, int> size_window = NcursesUtils::init();
  auto [ rows, cols ] = size_window;
  WINDOW* window = newwin(rows, cols, 0, 0);
  NcursesUtils::configure_input(window);


  //////////////////////////////////////////////////
  // Main loop
  //////////////////////////////////////////////////

  bool is_stereo = n_channels == 2;

  while (true) {
    // wait for key press (automatically calls refresh())
    int c = wgetch(window);
    if (c == 'q' || c == 'Q')
      break;

    ma_event_wait(&notification);

    // all audio frames were read
    ma_uint32 n_frames_available = ma_pcm_rb_available_read(&ring_buffer);
    if (n_frames_available == 0)
      break;

    // read samples chunk from ring buffer (1 frame = 1 sample for mono sound)
    int n_samples_chunk = n_frames_available * n_channels;
    std::vector<float> samples_chunk(n_samples_chunk);
    RingBuffer::read(samples_chunk.data(), ring_buffer, n_frames_available, format, n_channels);

    // draw mirrored bars (for each channel) for stereo & single mirroed bar for mono
    werase(window);

    if (is_stereo) {
      DrawerBar::draw_stereo(samples_chunk, window, size_window);;
    }
    else {
      DrawerBar::draw_mono(samples_chunk, window, size_window);;
    }

    // fps not used as the throughput of the stream coming from the audio device cannot be controlled!
    // napms(16); // fps ~ 60
  } // END MAIN LOOP


  //////////////////////////////////////////////////
  // Free resources
  //////////////////////////////////////////////////

  delwin(window);
  endwin();

  ma_event_uninit(&notification);
  ma_pcm_rb_uninit(&ring_buffer);
  ma_device_uninit(&device);
  ma_decoder_uninit(&decoder);

  std::cout << "Decoder format: " << format << std::endl;
  std::cout << "Decoder n_channels: " << n_channels << std::endl;
  std::cout << "rows: " << rows << std::endl;
  std::cout << "cols: " << cols << std::endl;

  return 0;
}
