#include "drawer_bars.hpp"
#include "conversion.hpp"
#include "bar.hpp"
#include "audio_utils.hpp"

/* Draw mono samples (mirrored vertically & from bottom-up) */
void DrawerBar::draw_mono(const Samples& samples, WINDOW* window, const SizeWindow& size_window) {
  size_t n_samples = samples.size();
  auto [ rows, cols ] = size_window;

  // samples intensities in terms of # of window rows & match each column with a chosen sample
  std::vector<int> rows_samples = Conversion::get_rows_samples(samples, rows);
  std::vector<int> indexes_samples_to_draw = Conversion::get_indexes_samples_by_col(n_samples, cols);

  // draw a bar at each window column
  for (int col = 0; col < cols; ++col) {
    int index_sample = indexes_samples_to_draw[col];
    int rows_sample = rows_samples[index_sample];
    Bar bar(col, rows);
    // bar.draw(window, 0, rows_sample, false);
    bar.draw(window, rows - 1, rows_sample, true);
  }
}

/**
 * Draw mirrored bars for left & right channels, organized such as:
 * Both have the same max height = floor(#rows / 2)
 * 1st vertical half (top) for left samples:
 *     - [ index_half - 1, 0 ] (bottom-to-top)
 * 2nd vertical half (bottom) for right samples (top-to-bottom):
 *     - [ index_half, #rows - 1 ] if even # samples
 *     - [ index_half, #rows - 2 ] if odd # samples
 */
void DrawerBar::draw_stereo(const Samples& samples, WINDOW* window, const SizeWindow& size_window) {
  auto [ rows, cols ] = size_window;
  int rows_half = rows / 2;

  // split frames into left & right samples for stereo
  auto [ samples_left, samples_right ] = AudioUtils::split_frames_by_channel(samples);

  // sample from same frame (left & right channels) drawn at the same window column
  int n_frames = samples.size() / 2;
  std::vector<int> indexes_samples_to_draw = Conversion::get_indexes_samples_by_col(n_frames, cols);

  std::vector<int> rows_samples_left = Conversion::get_rows_samples(samples_left, rows_half);
  std::vector<int> rows_samples_right = Conversion::get_rows_samples(samples_right, rows_half);

  // draw mirrored bar above half (left channel) & another one below it (right channel), at each window column
  for (int col = 0; col < cols; ++col) {
    int index_sample = indexes_samples_to_draw[col];
    int rows_sample_left = rows_samples_left[index_sample];
    int rows_sample_right = rows_samples_right[index_sample];

    Bar bar_left(col, rows_half);
    Bar bar_right(col, rows_half);

    bar_left.draw(window, rows_half - 1, rows_sample_left, true);
    bar_left.draw(window, rows_half, rows_sample_right, false);
  }
}
