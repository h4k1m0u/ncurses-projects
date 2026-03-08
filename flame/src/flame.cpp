#include "flame.hpp"
#include "symbols.hpp"

Flame::Flame(int rows, int cols, const Palette& palette):
  // ignore frame above/below & left/right & menu & grass (just below mario)
  m_rows(HEIGHT),
  m_cols(WIDTH),
  m_x(cols/2 - WIDTH/2),
  m_y(rows/2 - HEIGHT/2),
  m_sprite("images/frame1.png", palette)
{
}

WINDOW* Flame::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_y, m_x);

  return win;
}

void Flame::draw(WINDOW* window, [[ maybe_unused ]] int frame_index) {
  werase(window);

  m_sprite.draw(window, 0, 0);

  wrefresh(window);
}
