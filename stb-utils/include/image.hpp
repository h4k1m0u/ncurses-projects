#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>

// row-by-row
using ImagePixel = std::vector<unsigned char>;
using ImageRow = std::vector<ImagePixel>;
using ImageGrid = std::vector<ImageRow>;

/* Wrapper around stb-image */
struct Image {
private:
  unsigned char* m_data;

  unsigned char* get_data(const std::string& path_image);
  void free();

public:
  int width;
  int height;
  int n_channels;
  ImageGrid grid;

  Image() = default;
  Image(const std::string& path_image);
  ImageGrid get_grid();
};

#endif // IMAGE_HPP
