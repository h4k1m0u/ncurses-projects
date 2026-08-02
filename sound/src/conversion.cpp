#include "conversion.hpp"

namespace {
  /**
   * Convert sample intensity in [-1, 1] to row index in [0, rows - 1]
   * i.e. Finds the last row index to fill on the window
   * -1: at the very top
   *  0: at the center
   *  1: at the very bottom
   */
  int sample_to_row_index(float sample, int rows_window) {
    // sample shifted by offset=1, hence the 2 in the denominator
    return (sample + 1) * (rows_window - 1) / 2;
  }

  /**
   * Get index of chunk's sample to be drawn at given window's `col`
   * Sample chosen from a chunk of `n_samples_chunk` samples
   * Samples in [0, #samples_chunk - 1] and col in [0, #cols - 1]
   */
  int col_to_sample_index(int col, int cols_window, int n_samples_chunk) {
    return col * (n_samples_chunk - 1) / (cols_window - 1);
  }
}

/* Samples intensities in terms of # of window rows */
std::vector<int> Conversion::get_rows_samples(const std::vector<float>& samples_chunk, int rows_window) {
  int n_samples_chunk = samples_chunk.size();
  std::vector<int> rows_samples(n_samples_chunk);

  // #rows = row_index + 1 (as latter start from zero, i.e. in [0, #rows - 1])
  for (int i = 0; i < n_samples_chunk; i++) {
    float sample = samples_chunk[i];
    int row_index_sample = sample_to_row_index(sample, rows_window);
    rows_samples[i] = row_index_sample + 1;
  }

  return rows_samples;
}

/* Find index of sample drawn at each window column */
std::vector<int> Conversion::get_indexes_samples_by_col(int n_samples_chunk, int cols) {
  std::vector<int> indexes_samples_to_draw(cols);

  for (int col = 0; col < cols; ++col) {
    int index_sample = col_to_sample_index(col, cols, n_samples_chunk);
    indexes_samples_to_draw[col] = index_sample;
  }

  return indexes_samples_to_draw;
}
