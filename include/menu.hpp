#ifndef MENU_HPP
#define MENU_HPP

#include "colors.hpp"
#include <ncurses.h>

class Menu {
private:
  /* inline members don't require an out-of-class definition (in cpp file) */
  inline static const std::vector<std::string> ITEMS = {
    "Start",
    "Stop",
    "Reverse",
    "Quit",
  };

  /* must be inline to be init at runtime (otherwise RHS has to be a compiler constant) */
  inline static const size_t N_ITEMS = ITEMS.size();
  static constexpr char SEPARATOR = '|';
  static constexpr int BORDER_THICKNESS = 1;

  int m_cols;
  int m_x;
  int m_y;
  size_t m_i_selected;
  int m_width_item;
  std::vector<int> m_n_chars_items;

  std::vector<int> get_n_chars_items();
  bool is_selected(size_t i);

public:
  static constexpr int HEIGHT = BORDER_THICKNESS + 1 + BORDER_THICKNESS;

  Menu(int rows, int cols);
  WINDOW* create_window();
  void navigate_left();
  void navigate_right();
  bool is_quit_selected();
  void draw_border(WINDOW* window, ColorPair color_pair);
  void draw_items(WINDOW* window, ColorPair color_pair);
};

#endif
