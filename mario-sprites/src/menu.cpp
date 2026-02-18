#include "menu.hpp"
#include "frame.hpp"
#include <ncurses.h>

Menu::Menu(int rows, int cols):
  m_cols(cols - 2*Frame::WIDTH),
  m_x(Frame::WIDTH),
  m_y(rows - Frame::HEIGHT - HEIGHT),
  m_width_item((m_cols - 2*BORDER_THICKNESS) / N_ITEMS),
  m_n_chars_items(get_n_chars_items()),
  m_i_selected(0)
{
}

std::vector<int> Menu::get_n_chars_items() {
  std::vector<int> widths(N_ITEMS);

  for (size_t i = 0; i < N_ITEMS; ++i) {
    const std::string& item = ITEMS[i];
    widths[i] = item.size();
  }

  return widths;
}

/* new window that doesn't cover all terminal (coords start from 0) */
WINDOW* Menu::create_window() {
  WINDOW* win = newwin(HEIGHT, m_cols, m_y, m_x);

  return win;
}

void Menu::navigate_left() {
  m_i_selected = m_i_selected == 0 ? N_ITEMS - 1 : m_i_selected - 1;
}

void Menu::navigate_right() {
  m_i_selected = m_i_selected == N_ITEMS - 1 ? 0 : m_i_selected + 1;
}

MenuItem Menu::get_selected() {
  return static_cast<MenuItem>(m_i_selected);
}

void Menu::draw_border(WINDOW* window, ColorPair color_pair) {
  // draw borders around window
  wattr_on(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
  box(window, ACS_VLINE, ACS_HLINE);
  wattr_off(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
}

void Menu::draw_items(WINDOW* window, ColorPair color_pair) {
  for (size_t i = 0; i < ITEMS.size(); ++i) {
    const std::string& menu_item = ITEMS[i];

    /* Menu item */
    if (i == m_i_selected)
      wattr_on(window, A_REVERSE | A_BOLD | COLOR_PAIR(color_pair), NULL);

    // leave space for border
    int n_chars_item = m_n_chars_items[i];
    int row = BORDER_THICKNESS;
    int col = BORDER_THICKNESS + (i * m_width_item + m_width_item / 2 - n_chars_item / 2);
    mvwprintw(window, row, col, "%s", menu_item.c_str());

    wattr_off(window, A_REVERSE | A_BOLD | COLOR_PAIR(color_pair), NULL);

    // separator
    if (i > 0) {
      wattr_on(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
      mvwaddch(window, row, BORDER_THICKNESS + i*m_width_item, '|');
      wattr_off(window, A_BOLD | COLOR_PAIR(color_pair), NULL);
    }
  }
}
