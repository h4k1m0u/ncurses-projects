#include <ncurses.h>
#include <ncurses-utils/symbols.hpp>
#include <cmath>

#include "bar.hpp"
#include "constants.hpp"

Bar::Bar(int col, int max_rows):
  m_col(col),
  m_max_rows(max_rows),
  m_pairs(get_pairs())
{
  init_cchars();
}

void Bar::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/**
 * Get pairs (slots) for colors
 * Colors pairs start from 1 (as 0 is reserved for default terminal color)
 */
std::vector<Pair> Bar::get_pairs() {
  std::vector colors = Constants::COLORS;
  size_t n_colors = Constants::COLORS.size();
  std::vector<Pair> pairs(n_colors);
  int pair = 1;

  for (size_t i = 0; i < n_colors; ++i) {
    ColorIndex color_index = Constants::COLORS[i];
    init_pair(pair, color_index, -1);
    pairs[i] = pair++;
  }

  return pairs;
}

/**
 * Draw `rows` boxs starting from `row0` & going from top-to-bottom (unless `reversed`=true)
 * x & y are coords of upper-left corner
 */
void Bar::draw(WINDOW* window, int row0, int rows, bool reversed) {
  int r = row0;
  int step = reversed ? -1 : 1;

  // careful of integer division
  int n_intervals = m_pairs.size();
  int size_interval = std::ceil((float) m_max_rows / n_intervals);

  for (int i = 0; i < rows; ++i) {
    int j = i / size_interval;
    Pair pair = m_pairs[j];

    wattr_on(window, COLOR_PAIR(pair), NULL);
    mvwadd_wch(window, r, m_col, &m_block_full);
    wattr_off(window, COLOR_PAIR(pair), NULL);

    r += step;
  }
}
