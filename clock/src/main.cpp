#include <iostream>
#include <stdexcept>

#include <ncurses-utils/ncurses_utils.hpp>
#include <ncurses-utils/palette.hpp>
#include <ncurses-utils/pairs.hpp>

#include "clock.hpp"
#include "time.hpp"
#include "constants.hpp"

/**
 * Create sprite from given image path &
 * find ncurses color indexes closest to its colors
 */
static Sprite create_sprite(const std::string& path_image, const Palette& palette, Pairs& pairs) {
  Image image(path_image);

  if (image.n_channels != Constants::N_CHANNELS || image.width != Constants::WIDTH || image.height != Constants::HEIGHT) {
    endwin();
    throw std::runtime_error("Invalid image (wrong size or # of channels)");
  }

  ColorsGrid colors_grid = image.get_colors_grid();
  Sprite sprite(colors_grid);
  pairs.append_to_colors_map(colors_grid, palette);

  return sprite;
}

int main() {
  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();

  if (rows < Clock::HEIGHT || cols < Clock::WIDTH) {
    endwin();
    std::cout << "Terminal not big enough" << '\n';
    return 0;
  }


  //////////////////////////////////////////////////
  // Load palette of 256 colors
  //////////////////////////////////////////////////

  Palette palette;
  palette.load_colors();


  //////////////////////////////////////////////////
  // Load images from command-line paths & append their colors to pairs:
  //////////////////////////////////////////////////

  Pairs pairs;
  std::array<Sprite, Constants::N_DIGITS> digits;

  for (int i = 0; i < Constants::N_DIGITS; ++i) {
    std::string path_image = "images/" + std::to_string(i) + ".png";
    digits[i] = create_sprite(path_image, palette, pairs);
  }

  std::string path_image = "images/colon.png";
  Sprite colon = create_sprite(path_image, palette, pairs);

  // initialize pairs from colors in each image
  PairsMap pairs_map = pairs.get_pairs_map();


  //////////////////////////////////////////////////
  // Clock & its window
  //////////////////////////////////////////////////

  Clock clock(rows, cols, digits, colon);
  WINDOW* window = clock.create_window();


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  NcursesUtils::configure_input(window);


  //////////////////////////////////////////////////
  // Main loop
  //////////////////////////////////////////////////

  int c = 0;
  bool is_quitting = false;

  while (!is_quitting) {
    // wait for key press (automatically calls refresh())
    // wrefresh(win);
    c = wgetch(window);

    Time::HHMMSS triplet_time = Time::get_current();
    clock.draw(window, triplet_time, pairs_map);

    if (c == 'q' || c == 'Q')
      is_quitting = true;

    // sleep for 50ms (cap fps at ~ 20)
    // napms(16); // fps ~ 60
    napms(50);
  }

  delwin(window);
  endwin();

  return 0;
}
