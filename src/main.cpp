#include <ncurses.h>

#include "constants.hpp"
#include "menu.hpp"

using namespace Constants;

size_t i_selected = 0;

int main() {
  // initialize ncurses
  initscr();

  // enable colors
  start_color();

  // assign default terminal's fg/bg colors to color=-1 in init_pair()
  use_default_colors();

  // # of lines & cols for entire terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  printf("# lines: %d, # cols: %d\n", rows, cols);

  // separate menu window that doesn't cover all terminal,
  // so it can be h/v centered
  Menu menu;
  WINDOW* window_menu = menu.create_window(rows, cols);

  // get typed character (by getch()) without waiting for '\n'
  cbreak();

  // allows to detect the arrow-key pressed (in getch)
  // keypad(stdscr, TRUE);
  keypad(window_menu, TRUE);

  // prevent character read by getch() from being printed on stdout
  noecho();

  // sets the cursor state to invisible
  curs_set(0);

  // draw borders around window
  menu.draw_border(window_menu);

  int c = 0;

  while (c != 'q' && c != 'Q' && !(menu.is_selected(I_LAST) && c == '\n')) {
    menu.draw_items(window_menu);

    ///
    mvaddch(0, 0, ACS_CKBOARD);
    refresh();
    ///

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window_menu);

    if (c == KEY_UP)
      menu.navigate_up();
    else if (c == KEY_DOWN)
      menu.navigate_down();
  }

  delwin(window_menu);
  endwin();

  return 0;
}
