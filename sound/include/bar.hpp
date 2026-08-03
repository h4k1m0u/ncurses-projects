#ifndef BAR_HPP
#define BAR_HPP

#include <ncurses.h>

/**
 * Represents a single vertical bar to be drawn at given column (top-to-bottom) & which corresponds to an audio sample (in [-1, 1])
 * Rendering performed using box symbols in the appropriate color
 */
class Bar {
public:
  Bar(int col);
  void draw(WINDOW* window, int row0, int rows, bool reversed);

private:
  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  /* Column where to draw vertical boxes */
  int m_col;

  void init_cchars();
};

#endif // BAR_HPP
