#include <ncurses.h>
#include <vector>

#include "digit.hpp"
// #include "ncurses-utils/ncurses_utils.hpp"

int main() {
  //////////////////////////////////////////////////
  // Init ncurses
  //////////////////////////////////////////////////

  // auto [ rows, cols ] = NcursesUtils::init();


  //////////////////////////////////////////////////
  // Configure input
  //////////////////////////////////////////////////

  // NcursesUtils::configure_input(window_menu);


  //////////////////////////////////////////////////
  // Load digits
  //////////////////////////////////////////////////

  constexpr size_t N_DIGITS = 10;
  std::vector<Glyph> glyphs_map(N_DIGITS);

  for (size_t i = 0; i < N_DIGITS; ++i) {
    std::string path_image = "images/" + std::to_string(i) + ".png";
    Digit image_digit(path_image);
    glyphs_map[i] = image_digit.glyph;
  }

  return 0;
}
