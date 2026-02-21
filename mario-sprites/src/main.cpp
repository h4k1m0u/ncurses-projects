#include <ncurses.h>

#include "menu.hpp"
#include "frame.hpp"
#include "colors.hpp"
#include "background.hpp"
#include "mario.hpp"
#include "menu_item.hpp"

#include "ncurses-utils/ncurses_utils.hpp"

using namespace Colors;

size_t i_selected = 0;

int main() {
  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();


  //////////////////////////////////////////////////
  // Windows
  //////////////////////////////////////////////////

  // frame borders surround terminal
  Frame frame(rows, cols);
  WINDOW* window_frame = frame.create_window();

  // separate menu window that doesn't cover all terminal,
  Menu menu(rows, cols);
  WINDOW* window_menu = menu.create_window();

  // background (stars and background)
  Background background(rows, cols);
  WINDOW* window_background = background.create_window();

  // mario
  Mario mario(rows, cols);
  WINDOW* window_mario = mario.create_window();


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  NcursesUtils::configure_input(window_menu);


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

  // green gradient for grass
  std::vector<ColorPair> greens_pairs = Colors::colors_pairs[GREEN_KEY];
  std::vector<ColorIndex> greens_indexes = Colors::colors_indexes[GREEN_KEY];

  for (size_t i = 0; i < greens_pairs.size(); ++i) {
    init_pair(greens_pairs[i], greens_indexes[i], -1);
  }

  // gray gradient for stars
  std::vector<ColorPair> grays_pairs = Colors::colors_pairs[GRAY_KEY];
  std::vector<ColorIndex> grays_indexes = Colors::colors_indexes[GRAY_KEY];

  for (size_t i = 0; i < grays_pairs.size(); ++i) {
    init_pair(grays_pairs[i], grays_indexes[i], -1);
  }

  // mario skin
  std::vector<ColorPair> mario_pairs = Colors::colors_pairs[MARIO_KEY];
  std::vector<ColorIndex> mario_indexes = Colors::colors_indexes[MARIO_KEY];

  for (size_t i = 0; i < mario_pairs.size(); ++i) {
    init_pair(mario_pairs[i], mario_indexes[i], -1);
  }

  //////////////////////////////////////////////////
  // Draw
  //////////////////////////////////////////////////

  // draw frame borders
  frame.draw(window_frame, blue_pair);

  // draw borders around menu window
  menu.draw_border(window_menu, red_pair);

  // draw grass, night sky gradients & stars
  background.draw(window_background, greens_pairs, grays_pairs);

  int c = 0;
  int frame_index = 0;

  bool is_playing = true;
  bool is_reversed = false;
  bool is_quitting = false;

  while (!is_quitting) {
    menu.draw_items(window_menu, red_pair);

    if (is_playing)
      mario.draw(window_mario, mario_pairs, is_reversed, frame_index++);

    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window_menu);

    if (c == KEY_LEFT)
      menu.navigate_left();
    else if (c == KEY_RIGHT)
      menu.navigate_right();
    else if (c == 'q' || c == 'Q')
      is_quitting = true;
    else if (c == '\n') {
      MenuItem menu_item_selected = menu.get_selected();

      switch (menu_item_selected) {
        case MenuItem::START:
          is_playing = true;
          break;
        case MenuItem::STOP:
          is_playing = false;
          break;
        case MenuItem::REVERSE:
          is_reversed = !is_reversed;
          break;
        case MenuItem::QUIT:
          is_quitting = true;
      }
    }

    // sleep for 50ms (cap fps at ~ 20)
    // napms(16); // fps ~ 60
    napms(50);
  }

  delwin(window_mario);
  delwin(window_background);
  delwin(window_frame);
  delwin(window_menu);
  endwin();

  return 0;
}
