#ifndef COLOR_HPP
#define COLOR_HPP

#include <vector>

using ColorInt = unsigned int;

struct Color {
  unsigned char red;
  unsigned char green;
  unsigned char blue;

  Color() = default;
  Color(unsigned char r, unsigned char g, unsigned char b);
  Color(ColorInt color_int);
  Color(const std::vector<unsigned char> color);

  ColorInt to_hex();
  float distance2(const Color& color_other) const;
};

#endif // COLOR_HPP
