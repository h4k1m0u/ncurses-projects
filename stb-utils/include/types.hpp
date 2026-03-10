#ifndef TYPES_IMAGE_HPP
#define TYPES_IMAGE_HPP

#include <vector>

using ColorInt = unsigned int;

// row-by-row, single component per grid cell
using ImagePixel = std::vector<unsigned char>;
using ImageRow = std::vector<ImagePixel>;
using ImageGrid = std::vector<ImageRow>;

// row-by-row, rgb as an int per grid cell
using ColorInt = unsigned int;
using ColorsRow = std::vector<ColorInt>;
using ColorsGrid = std::vector<ColorsRow>;

#endif
