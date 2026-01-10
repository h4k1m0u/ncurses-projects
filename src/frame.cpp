#include "frame.hpp"

Frame::Frame(int rows, int cols):
  m_rows(rows),
  m_cols(cols)
{
  init_cchars();
}

void Frame::init_cchars() {
  setcchar(&m_block_full, &Frame::BLOCK_FULL_WCHAR, A_NORMAL, 0, NULL);
  setcchar(&m_block_dark_shade, &Frame::BLOCK_DARK_SHADE_WCHAR, A_NORMAL, 0, NULL);
  setcchar(&m_block_medium_shade, &Frame::BLOCK_MEDIUM_SHADE_WCHAR, A_NORMAL, 0, NULL);
  setcchar(&m_block_light_shade, &Frame::BLOCK_LIGHT_SHADE_WCHAR, A_NORMAL, 0, NULL);
}

WINDOW* Frame::create_window() {
  // full-screen window (see: `man newwin`)
  WINDOW* win = newwin(0, 0, 0, 0);

  return win;
}

void Frame::draw(WINDOW* window) {
  draw_left_border(window);
  draw_right_border(window);
  draw_top_border(window);
  draw_bottom_border(window);
  wrefresh(window);
}

void Frame::draw_left_border(WINDOW* window) {
  for (int i = 0; i < m_rows; ++i) {
    mvwadd_wch(window, i, 0, &m_block_full);
    mvwadd_wch(window, i, 1, &m_block_dark_shade);
    mvwadd_wch(window, i, 2, &m_block_medium_shade);
    mvwadd_wch(window, i, 3, &m_block_light_shade);
  }
}

void Frame::draw_right_border(WINDOW* window) {
  for (int i = 0; i < m_rows; ++i) {
    mvwadd_wch(window, i, m_cols - 1, &m_block_full);
    mvwadd_wch(window, i, m_cols - 2, &m_block_dark_shade);
    mvwadd_wch(window, i, m_cols - 3, &m_block_medium_shade);
    mvwadd_wch(window, i, m_cols - 4, &m_block_light_shade);
  }
}

/* miter joint (i.e. 45 degrees angle with left & right borders) */
void Frame::draw_top_border(WINDOW* window) {
  for (int i = 0; i < m_cols; ++i) {
    mvwadd_wch(window, 0, i, &m_block_full);

    if (i >= 1 && i <= m_cols - 2)
      mvwadd_wch(window, 1, i, &m_block_dark_shade);

    if (i >= 2 && i <= m_cols - 3)
      mvwadd_wch(window, 2, i, &m_block_medium_shade);

    if (i >= 3 && i <= m_cols - 4)
      mvwadd_wch(window, 3, i, &m_block_light_shade);
  }
}

/* miter joint (i.e. 45 degrees angle with left & right borders) */
void Frame::draw_bottom_border(WINDOW* window) {
  for (int i = 0; i < m_cols; ++i) {
    mvwadd_wch(window, m_rows - 1, i, &m_block_full);

    if (i >= 1 && i <= m_cols - 2)
      mvwadd_wch(window, m_rows - 2, i, &m_block_dark_shade);

    if (i >= 2 && i <= m_cols - 3)
      mvwadd_wch(window, m_rows - 3, i, &m_block_medium_shade);

    if (i >= 3 && i <= m_cols - 4)
      mvwadd_wch(window, m_rows - 4, i, &m_block_light_shade);
  }
}
