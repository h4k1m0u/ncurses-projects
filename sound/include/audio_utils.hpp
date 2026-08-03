#ifndef AUDIO_UTILS_HPP
#define AUDIO_UTILS_HPP

#include "types.hpp"

namespace AudioUtils {
  std::pair<Samples, Samples> split_frames_by_channel(const Samples& samples_chunk);
}

#endif // AUDIO_UTILS_HPP
