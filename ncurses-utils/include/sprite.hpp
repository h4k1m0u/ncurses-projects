#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <ncurses.h>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include <stb-utils/image.hpp>

#include "palette.hpp"

using Pair = int;
using PairsMap = std::unordered_map<ColorInt, Pair>;
using ColorsMap = std::unordered_map<ColorInt, ColorIndex>;

// row-by-row
using ColorsRow = std::vector<ColorInt>;
using ColorsGrid = std::vector<ColorsRow>;

using PairsRow = std::vector<Pair>;
using PairsGrid = std::vector<PairsRow>;

/* Renders image using box symbols in the appropriate color */
class Sprite {
public:
  Sprite() = default;
  Sprite(const std::string& path_image, const Palette& palette);
  void load_colors(const Palette& palette);
  void draw(WINDOW* window, int row_offset, int col_offset);

protected:
  Image m_image;

private:
  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  ColorsGrid m_colors_grid;
  ColorsMap m_colors_map;
  PairsMap m_pairs_map;

  std::unordered_set<ColorInt> get_unique_colors();
  ColorsGrid get_colors_grid();
  ColorsMap get_colors_map(const Palette& palette);
  PairsMap get_pairs_map();

  void init_cchars();
};

#endif // SPRITE_HPP
