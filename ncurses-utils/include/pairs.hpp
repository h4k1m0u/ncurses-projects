#ifndef PAIRS_HPP
#define PAIRS_HPP

#include <unordered_set>

#include "types.hpp"
#include "palette.hpp"

/* All ncurses colors pairs managed in the same class (to avoid overwriting) */
class Pairs {
public:
  Pairs() = default;
  void append_to_colors_map(const ColorsGrid& colors_grid, const Palette& palette);
  PairsMap get_pairs_map();

private:
  ColorsMap m_colors_map;

  std::unordered_set<ColorInt> get_unique_colors(const ColorsGrid& colors_grid);
};

#endif // PAIRS_HPP
