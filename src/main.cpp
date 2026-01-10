#include <ncurses.h>

#include "constants.hpp"
#include "menu.hpp"
#include "frame.hpp"

using namespace Constants;

size_t i_selected = 0;

int main() {
  // set locale to utf-8 to support unicode characters to print frame border (otherwise prints gibberish)
  setlocale(LC_ALL, "");

  // initialize ncurses
  initscr();

  // enable colors
  start_color();

  // assign default terminal's fg/bg colors to color=-1 in init_pair()
  use_default_colors();

  // # of lines & cols for entire terminal
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  // printf("# lines: %d, # cols: %d\n", rows, cols);

  // frame borders surround terminal
  Frame frame(rows, cols);
  WINDOW* window_frame = frame.create_window();

  // separate menu window that doesn't cover all terminal,
  // so it can be h/v centered
  Menu menu(rows, cols);
  WINDOW* window_menu = menu.create_window();

  // get typed character (by getch()) without waiting for '\n'
  cbreak();

  // allows to detect the arrow-key pressed (in getch)
  // keypad(stdscr, TRUE);
  keypad(window_menu, TRUE);

  // prevent character read by getch() from being printed on stdout
  noecho();

  // sets the cursor state to invisible
  curs_set(0);

  // draw frame borders
  frame.draw(window_frame);

  // draw borders around menu window
  menu.draw_border(window_menu);

  int c = 0;

  while (c != 'q' && c != 'Q' && !(menu.is_selected(I_LAST) && c == '\n')) {
    menu.draw_items(window_menu);

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window_menu);

    if (c == KEY_UP)
      menu.navigate_up();
    else if (c == KEY_DOWN)
      menu.navigate_down();
  }

  delwin(window_frame);
  delwin(window_menu);
  endwin();

  return 0;
}
