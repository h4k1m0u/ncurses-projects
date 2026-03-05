#include "sprite.hpp"

#include "symbols.hpp"
#include <stb-utils/image.hpp>

Sprite::Sprite(const std::string& path_image):
  m_image(path_image)
{
  init_cchars();
}

void Sprite::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/* x & y are coords of upper-left corner */
void Sprite::draw(WINDOW* window, int row_offset, int col_offset) const {
  int n_channels = m_image.n_channels;
  const ImagePixel PIXEL_BLACK(n_channels, 0);

  for (int row = 0; row < m_image.height; ++row) {
    for (int col = 0; col < m_image.width; ++col) {
      ImagePixel pixel(n_channels);

      for (int channel = 0; channel < n_channels; ++channel) {
        unsigned char component = m_image.grid[row][col][0];
        pixel[channel] = component;
      } // END CHANNELS

      // black on white background
      if (pixel == PIXEL_BLACK) {
        int row_abs = row_offset + row;
        int col_abs = col_offset + col;
        mvwadd_wch(window, row_abs, col_abs, &m_block_full);
      }

    } // END COLS
  } // END ROWS
}
