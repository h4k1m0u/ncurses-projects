#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <ncurses.h>
#include <string>

#include "image.hpp"

/* Digits (0-9) and colon (:) */
class Character {
public:
  Character() = default;
  Character(const std::string& path_image);
  void draw(WINDOW* window, int row_offset, int col_offset) const;

private:
  Image::Glyph m_glyph;

  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  void init_cchars();
};

#endif // CHARACTER_HPP
