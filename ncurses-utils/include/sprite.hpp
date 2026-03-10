#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <ncurses.h>

#include <stb-utils/image.hpp>

#include "palette.hpp"
#include "types.hpp"

/* Renders image using box symbols in the appropriate color */
class Sprite {
public:
  Sprite() = default;
  Sprite(const ColorsGrid& colors_grid);

  void load_colors(const Palette& palette);
  void draw(WINDOW* window, int row_offset, int col_offset, const PairsMap& pairs_map) const;

private:
  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  ColorsGrid m_colors_grid;

  ColorsGrid get_colors_grid();

  void init_cchars();
};

#endif // SPRITE_HPP
