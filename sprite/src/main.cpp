#include <iostream>
#include <ctime>

#include <ncurses-utils/ncurses_utils.hpp>
#include <ncurses-utils/palette.hpp>
#include <ncurses-utils/pairs.hpp>

#include "animated_sprite.hpp"
#include "constants.hpp"

using namespace Constants;

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "USAGE: " << argv[0] << " IMAGE0 IMAGE1 IMAGE2..." << std::endl;
    return 1;
  }


  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  auto [ rows, cols ] = NcursesUtils::init();

  if (rows < HEIGHT || cols < WIDTH) {
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

  size_t n_images = argc - 1;
  std::vector<Sprite> sprites(n_images);
  // std::cout << "# images: " << n_images << std::endl;

  Pairs pairs;

  for (size_t i = 0; i < n_images; ++i) {
    std::string path_image = argv[i + 1];
    Image image(path_image);

    if (image.n_channels != N_CHANNELS || image.width != WIDTH || image.height != HEIGHT) {
      endwin();
      throw std::runtime_error("Invalid image (wrong size or # of channels)");
    }

    ColorsGrid colors_grid = image.get_colors_grid();
    sprites[i] = Sprite(colors_grid);
    pairs.append_to_colors_map(colors_grid, palette);

    // std::cout << "Path image " << std::to_string(i) << " " << path_image << std::endl;
  }

  // initialize pairs from colors in each image
  PairsMap pairs_map = pairs.get_pairs_map();


  //////////////////////////////////////////////////
  // Sprites & its window
  //////////////////////////////////////////////////

  AnimatedSprite animated_sprite(rows, cols, sprites);
  WINDOW* window = animated_sprite.create_window();


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  NcursesUtils::configure_input(window);


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

    animated_sprite.draw(window, pairs_map, frame_index++);

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
