#ifndef MARIO_HPP
#define MARIO_HPP

#include <ncurses.h>

#include <ncurses-utils/palette.hpp>
#include <ncurses-utils/sprite.hpp>

class Flame {
public:
  static constexpr int WIDTH = 96;
  static constexpr int HEIGHT = 96;

  Flame(int rows, int cols, const Palette& palette);
  WINDOW* create_window();
  void draw(WINDOW* window, int frame_index);

private:
  // pertaining to the window
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;

  // pertaining to the sprite
  Sprite m_sprite;
};

#endif
