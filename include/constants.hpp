#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string>

namespace Constants {
  constexpr int BORDER_THICKNESS = 1;
  constexpr int PADDING_X = 10;
  constexpr int PADDING_Y = 5;

  const std::vector<std::string> MENU = {
    "> Start",
    "> Save",
    "> Settings",
    "> Quit",
  };
  const size_t N_MENU_ITEMS = MENU.size();
  const size_t I_LAST = N_MENU_ITEMS - 1;

  constexpr int N_CHARS_FRAME = 4;
}

#endif
