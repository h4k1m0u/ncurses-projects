#include <ctime>
#include <ncurses.h>

#include <ncurses-utils/ncurses_utils.hpp>
#include <ncurses-utils/palette.hpp>

#include "bird.hpp"

int main() {
  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();


  //////////////////////////////////////////////////
  // Windows
  //////////////////////////////////////////////////

  WINDOW* window = newwin(rows, cols, 0, 0);


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  NcursesUtils::configure_input(window);


  //////////////////////////////////////////////////
  // Load colors from sprites
  //////////////////////////////////////////////////

  Palette palette;
  palette.load_colors();

  Bird bird(rows, cols, palette);


  //////////////////////////////////////////////////
  // Main loop
  //////////////////////////////////////////////////

  int c = 0;
  bool is_quitting = false;
  int frame_index = 0;

  while (!is_quitting) {

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window);

    bird.draw(window, frame_index++);

    if (c == 'q' || c == 'Q')
      is_quitting = true;

    // sleep for 50ms (cap fps at ~ 20)
    // napms(16); // fps ~ 60
    // napms(50);
    napms(100); // fps = 10
  }

  delwin(window);
  endwin();

  return 0;
}
