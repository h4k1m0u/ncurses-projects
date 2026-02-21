#include <stdexcept>

#include "digit.hpp"
#include "symbols.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Digit::Digit(const std::string& path_image) {
  unsigned char* data = load_image(path_image);
  data_to_glyph(data);
  stbi_image_free(data);

  init_cchars();
}

unsigned char* Digit::load_image(const std::string& path_image) {
  int width, height, n_channels;
  unsigned char* data = stbi_load(path_image.c_str(), &width, &height, &n_channels, 0);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  if (n_channels != 1 || width != WIDTH_DIGIT || height != HEIGHT_DIGIT) {
    stbi_image_free(data);
    throw std::runtime_error("Invalid image (not grayscale, or wrong size)");
  }

  return data;
}

void Digit::data_to_glyph(unsigned char* data) {
  for (int row = 0; row < HEIGHT_DIGIT; ++row) {
    for (int col = 0; col < WIDTH_DIGIT; ++col) {
      int i = row * WIDTH_DIGIT + col;
      unsigned char pixel = data[i];

      m_glyph[row][col] = pixel;
    }
  }
}

void Digit::init_cchars() {
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
}

/* x & y are coords of upper-left corner */
void Digit::draw(WINDOW* window, int row_offset, int col_offset) const {
  for (int row = 0; row < HEIGHT_DIGIT; ++row) {
    for (int col = 0; col < WIDTH_DIGIT; ++col) {
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
