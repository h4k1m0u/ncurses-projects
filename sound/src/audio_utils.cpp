#include <stdexcept>

#include "audio_utils.hpp"

/**
 * Interleaved frames samples: L1 R1, L2 R2 ... (Stereo frame = 2 samples for left & rigth)
 * https://miniaud.io/docs/manual/index.html
 */
std::pair<Samples, Samples> AudioUtils::split_frames_by_channel(const Samples& samples) {
  size_t n_samples = samples.size();
  if (n_samples % 2 != 0)
    throw std::runtime_error("Number of samples must be even");
  
  size_t n_frames = n_samples / 2;
  Samples samples_left(n_frames);
  Samples samples_right(n_frames);

  for (size_t i_frame = 0; i_frame < n_frames; ++i_frame) {
    size_t i_sample_left = 2 * i_frame;
    size_t i_sample_right = 2 * i_frame + 1;

    samples_left[i_frame] = samples[i_sample_left]; 
    samples_right[i_frame] = samples[i_sample_right]; 
  }

  return std::make_pair(samples_left, samples_right);
}
