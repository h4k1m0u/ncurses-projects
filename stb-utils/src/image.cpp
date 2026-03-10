#include <stdexcept>

#include "image.hpp"
#include "color.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(const std::string& path_image):
  m_data(get_data(path_image)),
  grid(get_grid())
{
  free();
}

unsigned char* Image::get_data(const std::string& path_image) {
  unsigned char* data = stbi_load(path_image.c_str(), &width, &height, &n_channels, 0);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  return data;
}

ImageGrid Image::get_grid() {
  ImagePixel pixel(n_channels);
  ImageRow row(width, pixel);
  ImageGrid grid(height, row);

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      for (int n = 0; n < n_channels; ++n) {
        int i = n_channels * (row * width + col) + n;
        unsigned char value = m_data[i];

        grid[row][col][n] = value;
      }
    }
  }

  return grid;
}

ColorsGrid Image::get_colors_grid() {
  ColorsGrid colors_grid(height);

  for (int row = 0; row < height; ++row) {
    ColorsRow colors_row(width);

    for (int col = 0; col < width; ++col) {
      ImagePixel pixel(n_channels);

      for (int channel = 0; channel < n_channels; ++channel) {
        unsigned char component = grid[row][col][channel];
        pixel[channel] = component;
      } // END CHANNELS

      Color color(pixel);
      colors_row[col] = color.to_hex();
    } // END COLS

    colors_grid[row] = colors_row;
  } // END ROWS

  return colors_grid;
}

void Image::free() {
  stbi_image_free(m_data);
  m_data = nullptr;
}
