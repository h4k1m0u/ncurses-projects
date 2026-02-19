#include <iostream>
#include <stdexcept>

#include "image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/**
 * Load image
 * @param p Image path
 */
Image::Image(const std::string& path) {
  // load image using its path
  std::cout << "Loading image: " << path << "\n";
  constexpr int DESIRED_CHANNELS = 1;
  data = stbi_load(path.c_str(), &width, &height, &n_channels, DESIRED_CHANNELS);

  if (data == NULL) {
    const char* error_message = stbi_failure_reason();
    throw std::runtime_error(error_message);
  }

  if (n_channels != 1) {
    free();
    throw std::runtime_error("Image must be grayscale");
  }
}

void Image::free() const {
  stbi_image_free(data);
}
