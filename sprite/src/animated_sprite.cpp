#include "animated_sprite.hpp"
#include "constants.hpp"

using namespace Constants;

AnimatedSprite::AnimatedSprite(int rows, int cols, const std::vector<Sprite>& sprites):
  // ignore frame above/below & left/right & menu & grass (just below mario)
  m_rows(HEIGHT),
  m_cols(WIDTH),
  m_x(cols/2 - WIDTH/2),
  m_y(rows/2 - HEIGHT/2),
  m_sprites(sprites)
{
}

WINDOW* AnimatedSprite::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_y, m_x);

  return win;
}

void AnimatedSprite::draw(WINDOW* window, PairsMap pairs_map, int frame_index) {
  werase(window);

  size_t n_sprites = m_sprites.size();
  size_t i_sprite = frame_index % n_sprites;
  m_sprites[i_sprite].draw(window, 0, 0, pairs_map);

  wrefresh(window);
}
