#include "conversion.hpp"

/**
 * Convert sample in [-1, 1] to [0, rows - 1] where:
 * -1: at the very top
 *  0: at the center
 *  1: at the very bottom
 */
int Conversion::sample_to_row(float sample, int n_rows_window) {
  // sample shifted by offset=1, hence the 2 in the denominator
  return (sample + 1) * (n_rows_window - 1) / 2;
}

/**
 * Get index of sample to choose from a chunk of `n_samples` samples, to draw it in given `col`
 * Samples in [0, #samples - 1] and col in [0, #cols - 1]
 */
int Conversion::get_sample_index(int col, int n_cols_window, int n_samples) {
  return col * (n_samples - 1) / (n_cols_window - 1);
}
