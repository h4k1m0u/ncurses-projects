#include "mario.hpp"
#include "menu.hpp"
#include "background.hpp"
#include "symbols.hpp"
#include "frame.hpp"
#include <ncurses.h>

Mario::Mario(int rows, int cols):
  // ignore frame above/below & left/right & menu & grass (just below mario)
  m_rows(HEIGHT),
  m_cols(cols - 2*Frame::WIDTH),
  m_x(Frame::WIDTH),
  m_y(rows - Frame::HEIGHT - Menu::HEIGHT - Background::HEIGHT_GRASS - HEIGHT),
  m_x_sprite(0)
{
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

WINDOW* Mario::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_y, m_x);

  return win;
}

void Mario::draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_mario, int frame_index) {
  werase(window);

  // animation too quick for fps = 20
  const CoordsByColor& coords_by_color = frame_index % 4 == 0 ? COORDS_MARIO_FRAME1 : COORDS_MARIO_FRAME2;
  int n_colors = coords_by_color.size();

  m_x_sprite++;

  for (int i = 0; i < n_colors; ++i) {
    ColorPair color_pair = colors_pairs_mario[i];
    const std::vector<Coord>& coords_color = coords_by_color[i];

    wattr_on(window, COLOR_PAIR(color_pair), NULL);

    for (const auto& [ row, col ] : coords_color) {
      // move mario to the right as frames are updated
      int x = col + m_x_sprite;

      // reappear at the left (wrap animation) if past the screen
      if (m_x_sprite > m_cols)
        m_x_sprite = 0;

      mvwadd_wch(window, row, x, &m_block_full);
    } // END COORDS FOR COLOR

    wattr_off(window, COLOR_PAIR(color_pair), NULL);

  } // END COLORS

  wrefresh(window);
}
