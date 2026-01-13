#include <ncurses.h>

#include "constants.hpp"
#include "gradient.hpp"
#include "menu.hpp"
#include "frame.hpp"
#include "colors.hpp"

using namespace Constants;
using namespace Colors;

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

  // gradient
  Gradient gradient(rows, cols);
  WINDOW* window_gradient = gradient.create_window();

  // get typed character (by getch()) without waiting for '\n'
  cbreak();

  // allows to detect the arrow-key pressed (in getch)
  // keypad(stdscr, TRUE);
  keypad(window_menu, TRUE);

  // prevent character read by getch() from being printed on stdout
  noecho();

  // sets the cursor state to invisible
  curs_set(0);

  //////////////////////////////////////////////////
  // Colors
  //////////////////////////////////////////////////

  // initialize colors pairs
  Colors::init_colors_pairs();
  Colors::init_colors_indexes();

  auto [ blue_pair, blue_index ] = Colors::get_color(BLUE_KEY, -1);
  auto [ red_pair, red_index ] = Colors::get_color(RED_KEY, 0);

  init_pair(blue_pair, blue_index, -1);
  init_pair(red_pair, red_index, -1);

  // grass gradient
  std::vector<ColorPair> greens_pairs = Colors::colors_pairs[GREEN_KEY];
  std::vector<ColorIndex> greens_indexes = Colors::colors_indexes[GREEN_KEY];

  for (size_t i = 0; i < greens_pairs.size(); ++i) {
    init_pair(greens_pairs[i], greens_indexes[i], -1);
  }

  //////////////////////////////////////////////////
  // Draw
  //////////////////////////////////////////////////

  // draw frame borders
  frame.draw(window_frame, blue_pair);

  // draw borders around menu window
  menu.draw_border(window_menu, red_pair);

  // draw gradient of yellow lines
  gradient.draw(window_gradient, greens_pairs);

  int c = 0;

  while (c != 'q' && c != 'Q' && !(menu.is_selected(I_LAST) && c == '\n')) {
    menu.draw_items(window_menu, red_pair);

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

  delwin(window_gradient);
  delwin(window_frame);
  delwin(window_menu);
  endwin();

  return 0;
}
