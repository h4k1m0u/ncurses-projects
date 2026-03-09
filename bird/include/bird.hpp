#ifndef BIRD_HPP
#define BIRD_HPP

#include <ncurses.h>

#include <ncurses-utils/palette.hpp>
#include <ncurses-utils/sprite.hpp>

class Bird {
public:
  static constexpr int WIDTH = 32;
  static constexpr int HEIGHT = 32;
  static constexpr int N_SPRITES = 5;

  Bird(int rows, int cols, const Palette& palette);
  WINDOW* create_window();
  void draw(WINDOW* window, int frame_index);

private:
  // pertaining to the window
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;

  // pertaining to the sprite
  std::vector<Sprite> m_sprites;

  std::vector<Sprite> get_sprites(const Palette& palette);
};

#endif
