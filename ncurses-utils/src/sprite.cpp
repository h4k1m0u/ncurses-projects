#include "sprite.hpp"
#include "symbols.hpp"

Sprite::Sprite(const ColorsGrid& colors_grid):
  m_colors_grid(colors_grid)
{
  init_cchars();
}

void Sprite::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/* x & y are coords of upper-left corner */
void Sprite::draw(WINDOW* window, int row_offset, int col_offset, const PairsMap& pairs_map) const {
  // white background is transparent
  constexpr ColorInt WHITE = 0xffffff;
  int height = m_colors_grid.size();
  int width = m_colors_grid.front().size();

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      ColorInt color_int = m_colors_grid[row][col];
      Pair pair = pairs_map.at(color_int);

      if (color_int == WHITE)
        continue;

      // draw box in given color
      wattr_on(window, COLOR_PAIR(pair), NULL);

      int row_abs = row_offset + row;
      int col_abs = col_offset + col;
      mvwadd_wch(window, row_abs, col_abs, &m_block_full);

      wattr_off(window, COLOR_PAIR(pair), NULL);

    } // END COLS
  } // END ROWS
}
