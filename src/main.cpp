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

  // terminal has colors capability
  if (has_colors()) {
    init_pair(COLOR_PAIR_BLUE4, Colors.at(COLOR_PAIR_BLUE4), -1);
    init_pair(COLOR_PAIR_RED0, Colors.at(COLOR_PAIR_RED0), -1);

    ///
    init_pair(COLOR_PAIR_YELLOW0, Colors.at(COLOR_PAIR_YELLOW0), -1);
    init_pair(COLOR_PAIR_YELLOW1, Colors.at(COLOR_PAIR_YELLOW1), -1);
    init_pair(COLOR_PAIR_YELLOW2, Colors.at(COLOR_PAIR_YELLOW2), -1);
    init_pair(COLOR_PAIR_YELLOW3, Colors.at(COLOR_PAIR_YELLOW3), -1);
    init_pair(COLOR_PAIR_YELLOW4, Colors.at(COLOR_PAIR_YELLOW4), -1);
    ///
  }

  // draw frame borders
  frame.draw(window_frame, COLOR_PAIR_BLUE4);

  // draw borders around menu window
  menu.draw_border(window_menu, COLOR_PAIR_RED0);

  ///
  constexpr wchar_t BLOCK_FULL_WCHAR = L'█';
  cchar_t m_block_full;
  setcchar(&m_block_full, &BLOCK_FULL_WCHAR, A_NORMAL, 0, NULL);
  WINDOW* win = newwin(rows - 2*4, cols - 2*4, 4, 4);

  for (int j = 0; j < cols - 2*4; ++j) {
    for (int i = 0; i < 2*5; i += 2) {
      int color_pair = i/2 + 6;
      wattr_on(win, COLOR_PAIR(color_pair), NULL);

      mvwadd_wch(win, i, j, &m_block_full);
      mvwadd_wch(win, i + 1, j, &m_block_full);

      wattr_off(win, COLOR_PAIR(color_pair), NULL);
    } // END ROWS
  } // END COLS
  wrefresh(win);
  ///

  int c = 0;

  while (c != 'q' && c != 'Q' && !(menu.is_selected(I_LAST) && c == '\n')) {
    menu.draw_items(window_menu, COLOR_PAIR_RED0);

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window_menu);

    if (c == KEY_UP)
      menu.navigate_up();
    else if (c == KEY_DOWN)
      menu.navigate_down();

    // sleep for 50ms (cap fps at ~ 20)
    // napms(16); // fps ~ 60
    napms(50);
  }

  delwin(window_frame);
  delwin(window_menu);
  endwin();

  return 0;
}
