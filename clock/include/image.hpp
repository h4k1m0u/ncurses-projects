#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <array>

/* Wrapper around stb-image */
class Image {
public:
  static constexpr int WIDTH = 5;
  static constexpr int HEIGHT = 7;

  using Glyph = std::array<std::array<unsigned char, Image::WIDTH>, Image::HEIGHT>;

  Image(const std::string& path_image);
  unsigned char* get_data(const std::string& path_image);
  Glyph get_glyph();
  void free();

private:
  unsigned char* data;
};

#endif // IMAGE_HPP
