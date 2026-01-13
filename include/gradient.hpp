#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include <ncurses.h>
#include <vector>

#include "colors.hpp"

class Gradient {
public:
  Gradient(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs);

private:
  int m_rows;
  int m_cols;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
};

#endif
