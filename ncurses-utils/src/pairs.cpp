#include <ncurses.h>

#include "pairs.hpp"

std::unordered_set<ColorInt> Pairs::get_unique_colors(const ColorsGrid& colors_grid) {
  std::unordered_set<ColorInt> colors_ints;

  for (const ColorsRow& colors_row : colors_grid)
    for (ColorInt color_int : colors_row)
      colors_ints.insert(color_int);

  return colors_ints;
}

void Pairs::append_to_colors_map(const ColorsGrid& colors_grid, const Palette& palette) {
  std::unordered_set<ColorInt> colors_ints = get_unique_colors(colors_grid);

  for (ColorInt color_int : colors_ints) {
    if (m_colors_map.contains(color_int))
      continue;

    Color color(color_int);
    ColorIndex color_index = palette.find_index_closest_color(color);
    m_colors_map[color_int] = color_index;
  }
}

PairsMap Pairs::get_pairs_map() {
  // pairs (slots) for sprite colors
  // colors pairs start from 1 (as 0 is reserved for default terminal color)
  PairsMap pairs_map;
  int pair = 1;

  for (const auto& [ color_int, color_index ] : m_colors_map) {
    init_pair(pair, color_index, -1);
    pairs_map[color_int] = pair++;
  }

  return pairs_map;
}
