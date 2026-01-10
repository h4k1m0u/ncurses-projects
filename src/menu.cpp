#include "menu.hpp"
#include "constants.hpp"

using namespace Constants;

Menu::Menu(int rows, int cols):
  m_rows(rows),
  m_cols(cols),
  m_i_selected(0)
{
}

WINDOW* Menu::create_window() {
  // new window that doesn't cover all terminal (coords start from 0)
  size_t width_menu = get_menu_width();
  int rows_menu = N_MENU_ITEMS + 2*BORDER_THICKNESS + 2*PADDING_Y;
  int cols_menu = width_menu + 2*BORDER_THICKNESS + 2*PADDING_X;
  int x_menu = m_rows / 2 - rows_menu / 2;
  int y_menu = m_cols / 2 - cols_menu / 2;
  WINDOW* win = newwin(rows_menu, cols_menu, x_menu, y_menu);

  return win;
}

size_t Menu::get_menu_width() {
  size_t width = 0;

  for (const std::string& menu_item : MENU) {
    width = std::max(menu_item.size(), width);
  }

  return width;
}

void Menu::navigate_up() {
  m_i_selected = m_i_selected == 0 ? I_LAST : m_i_selected - 1;
}

void Menu::navigate_down() {
  m_i_selected = m_i_selected == I_LAST ? 0 : m_i_selected + 1;
}

bool Menu::is_selected(size_t i) {
  return m_i_selected == i;
}

void Menu::draw_border(WINDOW* window) {
  // terminal has colors capability
  if (has_colors()) {
    init_pair(1, COLOR_BLUE, -1);
  }

  // draw borders around window
  wattr_on(window, A_BOLD | COLOR_PAIR(1), NULL);
  box(window, ACS_VLINE, ACS_HLINE);
  wattr_off(window, A_BOLD | COLOR_PAIR(1), NULL);
}

void Menu::draw_items(WINDOW* window) {
  for (size_t i = 0; i < MENU.size(); ++i) {
    const std::string& menu_item = MENU[i];

    if (i == m_i_selected)
      wattr_on(window, A_REVERSE | A_BOLD | COLOR_PAIR(1), NULL);
    else
      wattr_off(window, A_REVERSE | A_BOLD | COLOR_PAIR(1), NULL);

    // leave space for border
    int row = i + BORDER_THICKNESS + PADDING_Y;
    const int COL = BORDER_THICKNESS + PADDING_X;
    mvwprintw(window, row, COL, "%s", menu_item.c_str());
  }
}
