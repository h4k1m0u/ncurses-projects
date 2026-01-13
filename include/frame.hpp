#ifndef FRAME_HPP
#define FRAME_HPP

#include "colors.hpp"
#include <ncurses.h>

class Frame {
public:
  Frame(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, ColorPair color_pair);

private:
  int m_rows;
  int m_cols;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
  cchar_t m_block_dark_shade;
  cchar_t m_block_medium_shade;
  cchar_t m_block_light_shade;

  void init_cchars();
  void draw_left_border(WINDOW* window);
  void draw_right_border(WINDOW* window);
  void draw_top_border(WINDOW* window);
  void draw_bottom_border(WINDOW* window);
};

#endif
