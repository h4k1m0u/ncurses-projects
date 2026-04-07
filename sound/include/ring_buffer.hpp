#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include "miniaudio.h"

namespace RingBuffer {
  void write(void* src, ma_pcm_rb& ring_buffer, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels);
  void read(void* dst, ma_pcm_rb& ring_buffer, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels);
}

#endif // RING_BUFFER_HPP
