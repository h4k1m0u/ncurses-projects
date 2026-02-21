#include <ncurses.h>

#include "ncurses-utils/ncurses_utils.hpp"
#include "clock.hpp"

int main() {
  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();


  //////////////////////////////////////////////////
  // Windows
  //////////////////////////////////////////////////

  // load digits from images
  Clock clock(rows, cols);
  WINDOW* window_clock = clock.create_window();


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  NcursesUtils::configure_input(window_clock);


  //////////////////////////////////////////////////
  // Main loop
  //////////////////////////////////////////////////

  int c = 0;
  bool is_quitting = false;

  while (!is_quitting) {
    clock.draw(window_clock);

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window_clock);

    if (c == 'q' || c == 'Q')
      is_quitting = true;

    // sleep for 50ms (cap fps at ~ 20)
    // napms(16); // fps ~ 60
    napms(50);
  }

  delwin(window_clock);
  endwin();

  return 0;
}
