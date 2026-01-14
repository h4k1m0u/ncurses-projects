#include "colors.hpp"
#include <utility>

// definitions of global variables (needed in main)
ColorsPairs Colors::colors_pairs;
ColorsIndexes Colors::colors_indexes;

// private namespace
namespace {
  /* Support cases where color indexes (in range) are sorted in ASC or DESC */
  void append_color_pairs(const ColorName& color_name, const ColorsIndexesRange& pair_indexes, ColorPair& pair) {
    auto [ index_start, index_end ] = pair_indexes;
    ColorIndex index_max = std::max(index_start, index_end);
    ColorIndex index_min = std::min(index_start, index_end);
    int n = index_max - index_min + 1;

    for (int i = 0; i < n; ++i)
      Colors::colors_pairs[color_name].push_back(pair++);
  }

  void append_color_indexes(const ColorName& color_name, const ColorsIndexesRange& pair_indexes) {
    auto [ index_start, index_end ] = pair_indexes;
    ColorIndex index = index_start;

    if (index_start < index_end) {
      while (index <= index_end)
        Colors::colors_indexes[color_name].push_back(index++);
    }
    else {
      while (index >= index_end)
        Colors::colors_indexes[color_name].push_back(index--);
    }
  }
}

void Colors::init_colors_pairs() {
  // pairs (slots) for fg colors
  // colors pairs start from 1 (as 0 is reserved for default terminal color)
  ColorPair pair = 1;
  append_color_pairs(BLUE_KEY, BLUES_INDEXES, pair);
  append_color_pairs(GREEN_KEY, GREENS_INDEXES, pair);
  append_color_pairs(YELLOW_KEY, YELLOWS_INDEXES, pair);
  append_color_pairs(RED_KEY, REDS_INDEXES, pair);
  append_color_pairs(GRAY_KEY, GRAYS_INDEXES, pair);

  // pairs (slots) for bg colors
  append_color_pairs(GRAY_INV_KEY, GRAYS_INDEXES, pair);
}

void Colors::init_colors_indexes() {
  // colors indexes from palette included in terminal
  append_color_indexes(BLUE_KEY, BLUES_INDEXES);
  append_color_indexes(GREEN_KEY, GREENS_INDEXES);
  append_color_indexes(YELLOW_KEY, YELLOWS_INDEXES);
  append_color_indexes(RED_KEY, REDS_INDEXES);
  append_color_indexes(GRAY_KEY, GRAYS_INDEXES);
}

std::pair<ColorPair, ColorIndex> Colors::get_color(const ColorName& color_name, int i) {
  ColorPair pair;
  ColorIndex index;

  if (i == -1) {
    pair = colors_pairs[color_name].back();
    index = colors_indexes[color_name].back();
  } else {
    pair = colors_pairs[color_name][i];
    index = colors_indexes[color_name][i];
  }

  return std::make_pair(pair, index);
}
