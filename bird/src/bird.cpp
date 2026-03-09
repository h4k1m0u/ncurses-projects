#include "bird.hpp"

Bird::Bird(int rows, int cols, const Palette& palette):
  // ignore frame above/below & left/right & menu & grass (just below mario)
  m_rows(HEIGHT),
  m_cols(WIDTH),
  m_x(cols/2 - WIDTH/2),
  m_y(rows/2 - HEIGHT/2),
  m_sprites(get_sprites(palette))
{
}

std::vector<Sprite> Bird::get_sprites(const Palette& palette) {
  std::vector<Sprite> sprites(N_SPRITES);

  for (size_t i = 0; i < N_SPRITES; ++i) {
    std::string path_sprite = "images/frame" + std::to_string(i) + ".png";
    sprites[i] = Sprite(path_sprite, palette);
  }

  return sprites;
}

WINDOW* Bird::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_y, m_x);

  return win;
}

void Bird::draw(WINDOW* window, int frame_index) {
  werase(window);

  size_t i_sprite = frame_index % N_SPRITES;
  m_sprites[i_sprite].draw(window, m_y, m_x);

  wrefresh(window);
}
