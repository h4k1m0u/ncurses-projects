#ifndef COLORS_HPP
#define COLORS_HPP

#include <string>
#include <vector>
#include <unordered_map>

using ColorPair = short;        // 1st argument in init_pair() (number starting from 1)
using ColorIndex = int;         // 2nd argument in init_pair() (index of shell color)
using ColorName = std::string;  // key used to index maps
using ColorsIndexesRange = std::pair<ColorIndex, ColorIndex>;
using ColorsPairs = std::unordered_map<std::string, std::vector<ColorPair>>;
using ColorsIndexes = std::unordered_map<std::string, std::vector<ColorIndex>>;

namespace Colors {
  // colors indexes (map values) found using: `./utils/print_colors_256.sh -n`
  // blue: 17 (dark) - 21 (light)
  constexpr std::string BLUE_KEY = "blue";
  constexpr ColorsIndexesRange BLUES_INDEXES(17, 21);

  // green: 46 (less saturated) - 50 (less saturated)
  // inverted to draw grass from bottom to top (livelier color at the top)
  constexpr std::string GREEN_KEY = "green";
  // constexpr ColorsIndexesRange GREENS_INDEXES(46, 50);
  // constexpr ColorsIndexesRange GREENS_INDEXES(50, 46);
  constexpr ColorsIndexesRange GREENS_INDEXES(48, 46);

  // yellow: 230 (less saturated) - 226 (saturated)
  constexpr std::string YELLOW_KEY = "yellow";
  constexpr ColorsIndexesRange YELLOWS_INDEXES(226, 230);

  // red: 160 (red) - 164 (pink)
  constexpr std::string RED_KEY = "red";
  constexpr ColorsIndexesRange REDS_INDEXES(160, 164);

  // gray shades from white to black
  // inv: white on gray background
  constexpr std::string GRAY_KEY = "gray";
  constexpr std::string GRAY_INV_KEY = "gray_inv";
  // constexpr ColorsIndexesRange GRAYS_INDEXES(232, 255);
  constexpr ColorsIndexesRange GRAYS_INDEXES(255, 235);

  // colors indexes (`./utils/print_colors_256.sh -n`)
  void init_colors_indexes();
  void init_colors_pairs();
  std::pair<ColorPair, ColorIndex> get_color(const ColorName& color_name, int i);

  // global variables (to avoid passing them to functions each time)
  extern ColorsPairs colors_pairs;
  extern ColorsIndexes colors_indexes;
}

#endif
