#ifndef COLORS_HPP
#define COLORS_HPP

#include <string>
#include <vector>
#include <unordered_map>

using ColorPair = short;        // 1st argument in init_pair() (number starting from 1)
using ColorIndex = int;         // 2nd argument in init_pair() (index of shell color)
using ColorName = std::string;  // key used to index maps
using ColorsIndexesRange = std::pair<ColorIndex, ColorIndex>;
using ColorsPairs = std::unordered_map<ColorName, std::vector<ColorPair>>;
using ColorsIndexes = std::unordered_map<ColorName, std::vector<ColorIndex>>;

namespace Colors {
  // colors indexes (map values) found using: `./utils/print_colors_256.sh -n`
  // blue: 17 (dark) - 21 (light)
  constexpr ColorName BLUE_KEY = "blue";
  constexpr ColorsIndexesRange BLUES_INDEXES(17, 21);

  // green: 46 (less saturated) - 50 (less saturated)
  // inverted to draw grass from bottom to top (livelier color at the top)
  constexpr ColorName GREEN_KEY = "green";
  // constexpr ColorsIndexesRange GREENS_INDEXES(46, 50);
  // constexpr ColorsIndexesRange GREENS_INDEXES(50, 46);
  constexpr ColorsIndexesRange GREENS_INDEXES(48, 46);

  // yellow: 230 (less saturated) - 226 (saturated)
  constexpr ColorName YELLOW_KEY = "yellow";
  constexpr ColorsIndexesRange YELLOWS_INDEXES(226, 230);

  // red: 160 (red) - 164 (pink)
  constexpr ColorName RED_KEY = "red";
  constexpr ColorsIndexesRange REDS_INDEXES(160, 164);

  // gray shades from white to black
  // inv: white on gray background
  constexpr ColorName GRAY_KEY = "gray";
  constexpr ColorName GRAY_INV_KEY = "gray_inv";
  // constexpr ColorsIndexesRange GRAYS_INDEXES(232, 255);
  constexpr ColorsIndexesRange GRAYS_INDEXES(255, 235);

  // mario skin (std::array not used so that functions can accept arrays with different lengths)
  constexpr int N_COLORS_MARIO = 3;
  constexpr ColorName MARIO_KEY = "mario";
  constexpr ColorIndex MARIO_INDEXES[N_COLORS_MARIO] = { 196, 215, 136 };

  // colors indexes (`./utils/print_colors_256.sh -n`)
  void init_colors_indexes();
  void init_colors_pairs();
  std::pair<ColorPair, ColorIndex> get_color(const ColorName& color_name, int i);

  // global variables (to avoid passing them to functions each time)
  extern ColorsPairs colors_pairs;
  extern ColorsIndexes colors_indexes;
}

#endif
