#include <ncurses-utils/symbols.hpp>

#include "bar.hpp"

Bar::Bar(int col):
  m_col(col)
{
  init_cchars();
}

void Bar::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/**
 * Draw `rows` boxs starting from `row0` & going from top-to-bottom (unless `reversed`=true)
 * x & y are coords of upper-left corner
 */
void Bar::draw(WINDOW* window, int row0, int rows, bool reversed) {
  int r = row0;
  int step = reversed ? -1 : 1;

  for (int i = 0; i < rows; ++i) {
    mvwadd_wch(window, r, m_col, &m_block_full);
    r += step;
  }
}
