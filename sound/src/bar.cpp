#include <ncurses-utils/symbols.hpp>

#include "bar.hpp"

Bar::Bar(int rows, int col):
  m_rows(rows),
  m_col(col)
{
  init_cchars();
}

void Bar::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/* x & y are coords of upper-left corner */
void Bar::draw(WINDOW* window) {
  for (int row = 0; row < m_rows; ++row) {
    mvwadd_wch(window, row, m_col, &m_block_full);
  }
}
