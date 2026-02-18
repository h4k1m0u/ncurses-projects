#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <random>
#include <array>
#include <ncurses.h>

#include "colors.hpp"

/* Stars above and grass below */
class Background {
public:
  static constexpr int HEIGHT_GRASS = 6;

  Background(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass, const std::vector<ColorPair>& colors_pairs_stars);

private:
  static constexpr int MAX_N_STARS_ROW = 10;
  static constexpr int N_STARS_SYMBOLS = 4;
  int m_rows;
  int m_cols;

  std::random_device m_seed;
  std::mt19937 m_generator;
  std::uniform_int_distribution<int> m_uniform_col;
  std::uniform_int_distribution<int> m_uniform_n_stars_row;
  std::uniform_int_distribution<int> m_uniform_stars_symbols;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
  std::array<cchar_t, 4> m_stars;

  void draw_grass(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass);
  void draw_stars(WINDOW* window, const std::vector<ColorPair>& colors_pairs_stars);
  void draw_stars_row(WINDOW* window, int row);
};

#endif
