#include <cmath>

#include "color.hpp"

Color::Color(unsigned char r, unsigned char g, unsigned char b):
  red(r),
  green(g),
  blue(b)
{
}

Color::Color(ColorInt color_int):
  red(color_int >> 16),
  green((color_int >> 8) & 0xff),
  blue(color_int & 0xff)
{
}

Color::Color(const std::vector<unsigned char> color):
  red(color[0]),
  green(color[1]),
  blue(color[2])
{
}

ColorInt Color::to_hex() {
  return (red << 16) | (green << 8) | blue;
}

float Color::distance2(const Color& color_other) const {
  return (
    std::pow(red - color_other.red, 2) + 
    std::pow(green - color_other.green, 2) + 
    std::pow(blue - color_other.blue, 2)
  );
}
