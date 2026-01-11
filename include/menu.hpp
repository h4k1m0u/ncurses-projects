#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>

class Menu {
public:
  Menu(int rows, int cols);
  WINDOW* create_window();
  void navigate_up();
  void navigate_down();
  bool is_selected(size_t i);
  void draw_border(WINDOW* window, int color_pair);
  void draw_items(WINDOW* window, int color_pair);

private:
  int m_rows;
  int m_cols;
  size_t m_i_selected;

  size_t get_menu_width();
};

#endif
