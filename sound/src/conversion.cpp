#include "conversion.hpp"

/**
 * Convert sample intensity in [-1, 1] to row index in [0, rows - 1]
 * i.e. Finds the last row index to fill on the window
 * -1: at the very top
 *  0: at the center
 *  1: at the very bottom
 */
int Conversion::sample_to_row_index(float sample, int n_rows_window) {
  // sample shifted by offset=1, hence the 2 in the denominator
  return (sample + 1) * (n_rows_window - 1) / 2;
}

/**
 * Get index of chunk's sample to be drawn at given window's `col`
 * Sample chosen from a chunk of `n_samples_chunk` samples
 * Samples in [0, #samples_chunk - 1] and col in [0, #cols - 1]
 */
int Conversion::col_to_sample_index(int col, int n_cols_window, int n_samples_chunk) {
  return col * (n_samples_chunk - 1) / (n_cols_window - 1);
}
