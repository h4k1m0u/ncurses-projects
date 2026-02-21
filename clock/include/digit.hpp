#ifndef DIGIT_HPP
#define DIGIT_HPP

#include <string>
#include <array>

constexpr int WIDTH_DIGIT = 5;
constexpr int HEIGHT_DIGIT = 7;
using Glyph = std::array<std::array<unsigned char, WIDTH_DIGIT>, HEIGHT_DIGIT>;

struct Digit {
  Glyph glyph;

  Digit(const std::string& p);
  void get_glyph(unsigned char* data);
};

#endif // DIGIT_HPP
