#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <ncurses.h>

#include <ncurses-utils/sprite.hpp>

class AnimatedSprite {
public:
  AnimatedSprite(int rows, int cols, const std::vector<Sprite>& sprites);
  WINDOW* create_window();
  void draw(WINDOW* window, PairsMap pairs_map, int frame_index);

private:
  // pertaining to the window
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;

  // pertaining to the sprites
  std::vector<Sprite> m_sprites;
};

#endif
