#include "mario.hpp"
#include "menu.hpp"
#include "background.hpp"
#include "symbols.hpp"
#include "frame.hpp"
#include "sprite.hpp"

using namespace Sprite;

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

void Mario::draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_mario, bool is_reversed, int frame_index) {
  werase(window);

  // animation too quick for fps = 20
  const CoordsByColor& coords_by_color = frame_index % 4 == 0 ? COORDS_MARIO_FRAME1 : COORDS_MARIO_FRAME2;
  int n_colors = coords_by_color.size();

  m_x_sprite += !is_reversed ? 1 : -1;

  // reappear at the left (wrap animation) if past the screen (zero-indexed coords)
  if (!is_reversed) {
    if (m_x_sprite > m_cols - 1)
      m_x_sprite = -(WIDTH - 1);
  } else {
    if (m_x_sprite < -(WIDTH - 1))
      m_x_sprite = m_cols - 1;
  }

  for (int i = 0; i < n_colors; ++i) {
    ColorPair color_pair = colors_pairs_mario[i];
    const std::vector<Coord>& coords_color = coords_by_color[i];

    wattr_on(window, COLOR_PAIR(color_pair), NULL);

    for (const auto& [ row, column ] : coords_color) {
      // mirror columns indexes rel. to middle vertical axis, if reversed
      int col = !is_reversed ? column : (WIDTH - 1) - column;

      // move mario to the right as frames are updated
      int x = col + m_x_sprite;

      mvwadd_wch(window, row, x, &m_block_full);
    } // END COORDS FOR COLOR

    wattr_off(window, COLOR_PAIR(color_pair), NULL);

  } // END COLORS

  wrefresh(window);
}
