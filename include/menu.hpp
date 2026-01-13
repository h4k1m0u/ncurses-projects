#ifndef MENU_HPP
#define MENU_HPP

#include "colors.hpp"
#include <ncurses.h>

class Menu {
public:
  Menu(int rows, int cols);
  WINDOW* create_window();
  void navigate_up();
  void navigate_down();
  bool is_selected(size_t i);
  void draw_border(WINDOW* window, ColorPair color_pair);
  void draw_items(WINDOW* window, ColorPair color_pair);

private:
  int m_width_menu_items;
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;
  size_t m_i_selected;

  int get_menu_items_width();
};

#endif
