#include "character.hpp"
#include "symbols.hpp"

Character::Character(const std::string& path_image) {
  Image image(path_image);
  m_glyph = image.get_glyph();
  image.free();

  init_cchars();
}

void Character::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/* x & y are coords of upper-left corner */
void Character::draw(WINDOW* window, int row_offset, int col_offset) const {
  for (int row = 0; row < Image::HEIGHT; ++row) {
    for (int col = 0; col < Image::WIDTH; ++col) {
      unsigned char pixel = m_glyph[row][col];

      // black on white background
      if (pixel == 0) {
        int row_abs = row_offset + row;
        int col_abs = col_offset + col;
        mvwadd_wch(window, row_abs, col_abs, &m_block_full);
      }
    }
  }
}
