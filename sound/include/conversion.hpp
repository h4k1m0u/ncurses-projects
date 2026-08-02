#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <vector>

/* Conversion between samples range [-1, 1] & screen coordinates (row, col) */
namespace Conversion {
  std::vector<int> get_rows_samples(const std::vector<float>& samples, int n_rows_window);
  std::vector<int> get_indexes_samples_by_col(int n_samples_chunk, int cols);
}

#endif // CONVERSION_HPP
