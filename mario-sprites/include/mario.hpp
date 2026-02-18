#ifndef MARIO_HPP
#define MARIO_HPP

#include <ncurses.h>

#include "colors.hpp"

class Mario {
public:
  static constexpr int WIDTH = 16;
  static constexpr int HEIGHT = 16;

  Mario(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_mario, bool is_reversed, int frame_index);

private:
  // pertaining to the window
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;

  // pertaining to the sprite
  int m_x_sprite;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
};

#endif
