#include <iostream>
#include <stdexcept>

#include "digit.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Digit::Digit(const std::string& path) {
  std::cout << "Loading image: " << path << "\n";
  int width, height, n_channels;
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &n_channels, 0);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  if (n_channels != 1 || width != WIDTH_DIGIT || height != HEIGHT_DIGIT) {
    stbi_image_free(data);
    throw std::runtime_error("Invalid image (not grayscale, or wrong size)");
  }

  get_glyph(data);
  stbi_image_free(data);
}

void Digit::get_glyph(unsigned char* data) {
  for (int row = 0; row < HEIGHT_DIGIT; ++row) {
    for (int col = 0; col < WIDTH_DIGIT; ++col) {
      int i = row * WIDTH_DIGIT + col;
      unsigned char pixel = data[i];

      glyph[row][col] = pixel;
    }
  }
}
