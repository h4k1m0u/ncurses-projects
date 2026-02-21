#include <stdexcept>

#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const std::string& path_image):
  data(get_data(path_image))
{
}

unsigned char* Image::get_data(const std::string& path_image) {
  int width, height, n_channels;
  unsigned char* data = stbi_load(path_image.c_str(), &width, &height, &n_channels, 0);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  if (n_channels != 1 || width != Image::WIDTH || height != Image::HEIGHT) {
    free();
    throw std::runtime_error("Invalid image (not grayscale, or wrong size)");
  }

  return data;
}

Image::Glyph Image::get_glyph() {
  Image::Glyph glyph;

  for (int row = 0; row < Image::HEIGHT; ++row) {
    for (int col = 0; col < Image::WIDTH; ++col) {
      int i = row * Image::WIDTH + col;
      unsigned char pixel = data[i];

      glyph[row][col] = pixel;
    }
  }

  return glyph;
}

void Image::free() {
  stbi_image_free(data);
}
