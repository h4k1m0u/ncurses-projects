#include <stdexcept>
#include <iostream>

#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const std::string& path_image):
  m_data(get_data(path_image))
{
}

unsigned char* Image::get_data(const std::string& path_image) {
  unsigned char* data = stbi_load(path_image.c_str(), &width, &height, &n_channels, 0);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  return data;
}

ImageData Image::get_glyph() {
  ImagePixel pixel(n_channels);
  ImageRow row(width, pixel);
  ImageData glyph(height, row);

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      for (int n = 0; n < n_channels; ++n) {
        int i = n_channels * (row * width + col) + n;
        unsigned char value = m_data[i];

        glyph[row][col][n] = value;
      }
    }
  }

  return glyph;
}

void Image::free() {
  stbi_image_free(m_data);
}
