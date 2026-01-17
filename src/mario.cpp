#include "mario.hpp"
#include "menu.hpp"
#include "symbols.hpp"
#include "frame.hpp"
#include <ncurses.h>

Mario::Mario(int rows, int cols):
  // ignore frame above/below & left/right
  m_rows(rows - 2*Frame::HEIGHT - Menu::HEIGHT),
  m_cols(cols - 2*Frame::HEIGHT)
{
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

WINDOW* Mario::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, Frame::HEIGHT, Frame::HEIGHT);

  return win;
}

void Mario::draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_mario, int frame_index) {
  werase(window);

  // animation too quick for fps = 20
  const CoordsByColor& coords_by_color = frame_index % 4 == 0 ? COORDS_MARIO_FRAME1 : COORDS_MARIO_FRAME2;
  int n_colors = coords_by_color.size();

  for (int i = 0; i < n_colors; ++i) {
    ColorPair color_pair = colors_pairs_mario[i];
    const std::vector<Coord>& coords_color = coords_by_color[i];

    wattr_on(window, COLOR_PAIR(color_pair), NULL);

    for (const auto& [ row, col ] : coords_color) {
      // move mario as frames are updated
      int row_mario = row;
      int col_mario = col + frame_index;
      mvwadd_wch(window, row_mario, col_mario, &m_block_full);
    } // END COORDS FOR COLOR

    wattr_off(window, COLOR_PAIR(color_pair), NULL);

  } // END COLORS

  wrefresh(window);
}
