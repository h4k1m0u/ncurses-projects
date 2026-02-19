#include <iostream>

#include "image.hpp"

int main() {
  Image image_digit0("images/0.png");

  for (int row = 0; row < Image::HEIGHT; ++row) {
    for (int col = 0; col < Image::WIDTH; ++col) {
      int i = row * Image::WIDTH + col;
      unsigned char pixel = image_digit0.data[i];
    
      std::cout << "x, y: " << col << ", " << row
                << " value: " << (int) pixel << std::endl;
    }
  }

  image_digit0.free();

  return 0;
}
