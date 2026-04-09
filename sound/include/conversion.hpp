#ifndef CONVERSION_HPP
#define CONVERSION_HPP

/* Conversion between samples range [-1, 1] & screen coordinates (row, col) */
namespace Conversion {
  int sample_to_row(float sample, int n_rows_window);
  int get_sample_index(int col, int n_cols_window, int n_samples);
}

#endif // CONVERSION_HPP
