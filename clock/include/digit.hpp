#ifndef DIGIT_HPP
#define DIGIT_HPP

#include <ncurses.h>
#include <string>
#include <array>

class Digit {
public:
  static constexpr int WIDTH_DIGIT = 5;
  static constexpr int HEIGHT_DIGIT = 7;
  using Glyph = std::array<std::array<unsigned char, WIDTH_DIGIT>, HEIGHT_DIGIT>;

  Digit() = default;
  Digit(const std::string& path_image);
  void draw(WINDOW* window, int row_offset, int col_offset) const;

private:
  Glyph m_glyph;

  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  unsigned char* load_image(const std::string& path_image);
  void data_to_glyph(unsigned char* data);
  void init_cchars();
};

#endif // DIGIT_HPP
