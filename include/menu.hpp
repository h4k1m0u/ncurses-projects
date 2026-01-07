#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>

class Menu {
public:
  Menu();
  WINDOW* create_window(int rows, int cols);
  void navigate_up();
  void navigate_down();
  bool is_selected(size_t i);
  void draw_border(WINDOW* window);
  void draw_items(WINDOW* window);

private:
  size_t m_i_selected;

  size_t get_menu_width();
};

#endif
