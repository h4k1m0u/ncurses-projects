#ifndef FRAME_HPP
#define FRAME_HPP

#include <ncurses.h>

class Frame {
public:
  Frame(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, int color_pair);

private:
  int m_rows;
  int m_cols;

  /**
   * wchar_t literal (can hold UTF-32 on linux, UTF-16 on windows)
   * Sorted from lightest to darkest (Light Shade is the darkest when rendered on the terminal!)
   * constexpr static implies inline AND inline static class members don't require an out-of-class definition
   * (i.e. a definition in cpp file like for static const)
   */
  // echo -e '\u2588\u2593\u2592\u2591'
  static constexpr wchar_t BLOCK_FULL_WCHAR = L'█';         // Full Block:  '\u2588'
  static constexpr wchar_t BLOCK_DARK_SHADE_WCHAR = u'▓';   // Dark Shade:  '\u2593'
  static constexpr wchar_t BLOCK_MEDIUM_SHADE_WCHAR = u'▒'; // Dark Shade:  '\u2592'
  static constexpr wchar_t BLOCK_LIGHT_SHADE_WCHAR = u'░';  // Light Shade: '\u2591'

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
