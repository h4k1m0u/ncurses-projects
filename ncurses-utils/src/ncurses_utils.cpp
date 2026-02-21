#include <locale.h>

#include "ncurses_utils.hpp"

std::pair<int, int> NcursesUtils::init() {
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

  return std::make_pair(rows, cols);
}

void NcursesUtils::configure_input(WINDOW* window) {
  // get typed character (by getch()) without waiting for '\n'
  cbreak();

  // allows to detect the arrow-key pressed (in getch)
  // keypad(stdscr, TRUE);
  keypad(window, TRUE);

  // prevent character read by getch() from being printed on stdout
  noecho();

  // sets the cursor state to invisible
  curs_set(0);

  // set getch() to be non-blocking (to animate mario)
  nodelay(window, TRUE);
}
