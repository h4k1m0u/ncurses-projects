#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

/* Wrapper around image pointer returned by `stbi_load()` */
struct Image {
  int width;
  int height;
  int n_channels;
  unsigned char* data;

  static constexpr int WIDTH = 5;
  static constexpr int HEIGHT = 7;

  Image(const std::string& p);
  void free() const;

private:
};

#endif // IMAGE_HPP
