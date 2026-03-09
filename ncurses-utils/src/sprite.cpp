#include "sprite.hpp"
#include "symbols.hpp"

Sprite::Sprite(const std::string& path_image, const Palette& palette):
  m_image(path_image),
  m_colors_grid(get_colors_grid()),
  m_colors_map(get_colors_map(palette)),
  m_pairs_map(get_pairs_map())
{
  init_cchars();
}

void Sprite::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

ColorsGrid Sprite::get_colors_grid() {
  int n_channels = m_image.n_channels;
  int width = m_image.width;
  int height = m_image.height;
  ColorsGrid colors_grid(height);

  for (int row = 0; row < height; ++row) {
    ColorsRow colors_row(width);

    for (int col = 0; col < width; ++col) {
      ImagePixel pixel(n_channels);

      for (int channel = 0; channel < n_channels; ++channel) {
        unsigned char component = m_image.grid[row][col][channel];
        pixel[channel] = component;
      } // END CHANNELS

      Color color(pixel);
      colors_row[col] = color.to_hex();
    } // END COLS

    colors_grid[row] = colors_row;
  } // END ROWS

  return colors_grid;
}

std::unordered_set<ColorInt> Sprite::get_unique_colors() {
  std::unordered_set<ColorInt> colors_ints;

  for (const ColorsRow& colors_row : m_colors_grid)
    for (ColorInt color_int : colors_row)
      colors_ints.insert(color_int);

  return colors_ints;
}

ColorsMap Sprite::get_colors_map(const Palette& palette) {
  std::unordered_set<ColorInt> colors_ints = get_unique_colors();
  std::unordered_map<ColorInt, ColorIndex> colors_map;

  for (ColorInt color_int : colors_ints) {
    Color color(color_int);
    ColorIndex color_index = palette.find_index_closest_color(color);
    colors_map[color_int] = color_index;
  }

  return colors_map;
}

PairsMap Sprite::get_pairs_map() {
  // pairs (slots) for sprite colors
  // colors pairs start from 1 (as 0 is reserved for default terminal color)
  PairsMap pairs_map;
  int pair = 1;

  for (const auto& [ color_int, color_index ] : m_colors_map) {
    init_pair(pair, color_index, -1);
    m_pairs_map[color_int] = pair++;
  }

  return pairs_map;
}

/* x & y are coords of upper-left corner */
void Sprite::draw(WINDOW* window, int row_offset, int col_offset) {
  // white background is transparent
  constexpr ColorInt WHITE = 0xffffff;

  for (int row = 0; row < m_image.height; ++row) {
    for (int col = 0; col < m_image.width; ++col) {
      ColorInt color_int = m_colors_grid[row][col];
      Pair pair = m_pairs_map[color_int];

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
