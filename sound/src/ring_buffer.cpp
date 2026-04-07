#include <iostream>

#include "ring_buffer.hpp"

/* Copy `n_frames` frames from `src` to ring buffer */
void RingBuffer::write(void* src, ma_pcm_rb& ring_buffer, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels) {
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
void RingBuffer::read(void* dst, ma_pcm_rb& ring_buffer, ma_uint64 n_frames, ma_format format, ma_uint32 n_channels) {
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
