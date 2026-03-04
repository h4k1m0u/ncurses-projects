#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <ncurses.h>
#include <string>

#include <stb-utils/image.hpp>

/* Digits (0-9) and colon (:) */
class Character {
public:
  static constexpr int WIDTH = 5;
  static constexpr int HEIGHT = 7;
  static constexpr int N_CHANNELS = 1;

  Character() = default;
  Character(const std::string& path_image);
  void draw(WINDOW* window, int row_offset, int col_offset) const;

private:
  ImageData m_glyph;

  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  void init_cchars();
};

#endif // CHARACTER_HPP
