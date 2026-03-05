#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <ncurses.h>
#include <string>

#include <stb-utils/image.hpp>

/* Renders image using box symbols in the appropriate color */
class Sprite {
public:
  Sprite() = default;
  Sprite(const std::string& path_image);
  void draw(WINDOW* window, int row_offset, int col_offset) const;

protected:
  Image m_image;

private:
  /* cchar_t used to hold C wide-characters for n-curses (unicode constants like emojis stored in wchar_t) */
  cchar_t m_block_full;

  void init_cchars();
};

#endif // SPRITE_HPP
