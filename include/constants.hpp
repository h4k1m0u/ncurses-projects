#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <vector>
#include <string>
#include <unordered_map>

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

  // colors indexes (map values) found using: `./utils/print_colors_256.sh -n`
  // colors pairs start from 1 (as 0 is reserved for default terminal color)
  // blue: 17 (dark) - 21 (light)
  constexpr int BLUE0 = 17;
  constexpr int BLUE1 = 18;
  constexpr int BLUE2 = 19;
  constexpr int BLUE3 = 20;
  constexpr int BLUE4 = 21;

  constexpr int COLOR_PAIR_BLUE0 = 1;
  constexpr int COLOR_PAIR_BLUE1 = 2;
  constexpr int COLOR_PAIR_BLUE2 = 3;
  constexpr int COLOR_PAIR_BLUE3 = 4;
  constexpr int COLOR_PAIR_BLUE4 = 5;

  // yellow: 226 (saturated) - 230 (less saturated)
  constexpr int YELLOW0 = 226;
  constexpr int YELLOW1 = 227;
  constexpr int YELLOW2 = 228;
  constexpr int YELLOW3 = 229;
  constexpr int YELLOW4 = 230;

  constexpr int COLOR_PAIR_YELLOW0 = 6;
  constexpr int COLOR_PAIR_YELLOW1 = 7;
  constexpr int COLOR_PAIR_YELLOW2 = 8;
  constexpr int COLOR_PAIR_YELLOW3 = 9;
  constexpr int COLOR_PAIR_YELLOW4 = 10;

  // red: 160 (red) - 164 (pink)
  constexpr int RED0 = 160;
  constexpr int RED1 = 161;
  constexpr int RED2 = 162;
  constexpr int RED3 = 163;
  constexpr int RED4 = 164;

  constexpr int COLOR_PAIR_RED0 = 11;
  constexpr int COLOR_PAIR_RED1 = 12;
  constexpr int COLOR_PAIR_RED2 = 13;
  constexpr int COLOR_PAIR_RED3 = 14;
  constexpr int COLOR_PAIR_RED4 = 15;

  const std::unordered_map<int, int> Colors = {
    { COLOR_PAIR_BLUE0 , BLUE0 },
    { COLOR_PAIR_BLUE1 , BLUE1 },
    { COLOR_PAIR_BLUE2 , BLUE2 },
    { COLOR_PAIR_BLUE3 , BLUE3 },
    { COLOR_PAIR_BLUE4 , BLUE4 },

    { COLOR_PAIR_YELLOW0 , YELLOW0 },
    { COLOR_PAIR_YELLOW1 , YELLOW1 },
    { COLOR_PAIR_YELLOW2 , YELLOW2 },
    { COLOR_PAIR_YELLOW3 , YELLOW3 },
    { COLOR_PAIR_YELLOW4 , YELLOW4 },

    { COLOR_PAIR_RED0 , RED0 },
    { COLOR_PAIR_RED1 , RED1 },
    { COLOR_PAIR_RED2 , RED2 },
    { COLOR_PAIR_RED3 , RED3 },
    { COLOR_PAIR_RED4 , RED4 },
  };
}

#endif
