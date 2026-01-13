#include "gradient.hpp"
#include "blocks.hpp"
#include "constants.hpp"

using namespace Constants;

Gradient::Gradient(int rows, int cols):
  // ignore frame above/below & left/right
  m_rows(rows - 2*N_CHARS_FRAME),
  m_cols(cols - 2*N_CHARS_FRAME)
{
  setcchar(&m_block_full, &Blocks::FULL_WCHAR, A_NORMAL, 0, NULL);
}

WINDOW* Gradient::create_window() {
  // full-screen window (see: `man newwin`)
  WINDOW* win = newwin(m_rows, m_cols, N_CHARS_FRAME, N_CHARS_FRAME);

  return win;
}

void Gradient::draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs) {
  int n_colors = colors_pairs.size();

  for (int col = 0; col < m_cols; ++col) {
    for (int i = 0; i < n_colors; i++) {
      int color_pair = colors_pairs[i];
      wattr_on(window, COLOR_PAIR(color_pair), NULL);

      // pair of rows in same color, starting from those just above frame (grass)
      int row = (m_rows - 1) - 2*i;
      mvwadd_wch(window, row, col, &m_block_full);
      mvwadd_wch(window, row - 1, col, &m_block_full);

      wattr_off(window, COLOR_PAIR(color_pair), NULL);
    } // END ROWS
  } // END COLS

  wrefresh(window);
}
