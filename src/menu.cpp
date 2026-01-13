#include "menu.hpp"
#include "constants.hpp"

using namespace Constants;

Menu::Menu(int rows, int cols):
  m_width_menu_items(get_menu_items_width()),
  m_rows(N_MENU_ITEMS + 2*BORDER_THICKNESS + 2*PADDING_Y),
  m_cols(m_width_menu_items + 2*BORDER_THICKNESS + 2*PADDING_X),
  m_x(rows / 2 - m_rows / 2),
  m_y(cols / 2 - m_cols / 2),
  m_i_selected(0)
{
}

/* new window that doesn't cover all terminal (coords start from 0) */
WINDOW* Menu::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_x, m_y);

  return win;
}

int Menu::get_menu_items_width() {
  int width = 0;

  for (const std::string& menu_item : MENU) {
    int n_chars_item = menu_item.size();
    width = std::max(n_chars_item, width);
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

void Menu::draw_border(WINDOW* window, ColorPair color_pair) {
  // draw borders around window
  wattr_on(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
  box(window, ACS_VLINE, ACS_HLINE);
  wattr_off(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
}

void Menu::draw_items(WINDOW* window, ColorPair color_pair) {
  for (size_t i = 0; i < MENU.size(); ++i) {
    const std::string& menu_item = MENU[i];

    if (i == m_i_selected)
      wattr_on(window, A_REVERSE | A_BOLD | COLOR_PAIR(color_pair), NULL);
    else
      wattr_off(window, A_REVERSE | A_BOLD | COLOR_PAIR(color_pair), NULL);

    // leave space for border
    int row = i + BORDER_THICKNESS + PADDING_Y;
    const int COL = BORDER_THICKNESS + PADDING_X;
    mvwprintw(window, row, COL, "%s", menu_item.c_str());

  }
}
