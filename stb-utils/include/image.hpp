#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

// row-by-row
using ImagePixel = std::vector<unsigned char>;
using ImageRow = std::vector<ImagePixel>;
using ImageData = std::vector<ImageRow>;

/* Wrapper around stb-image */
struct Image {
public:
  int width;
  int height;
  int n_channels;

  Image(const std::string& path_image);
  unsigned char* get_data(const std::string& path_image);
  ImageData get_glyph();
  void free();

private:
  unsigned char* m_data;
};

#endif // IMAGE_HPP
