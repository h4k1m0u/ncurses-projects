#ifndef SCENE_HPP
#define SCENE_HPP

#include <random>
#include <ncurses.h>

#include "colors.hpp"

class Scene {
public:
  Scene(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars);

private:
  static constexpr int MAX_N_STARS_ROW = 4;
  int m_rows;
  int m_cols;

  std::random_device m_seed;
  std::mt19937 m_generator;
  std::uniform_int_distribution<int> m_uniform_row;
  std::uniform_int_distribution<int> m_uniform_col;
  std::uniform_int_distribution<int> m_uniform_symbols;
  std::uniform_int_distribution<int> m_uniform_n_stars_row;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
  cchar_t m_star;

  void draw_grass(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass);
  void draw_sky(WINDOW* window, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars);
  void draw_stars_row(WINDOW* window, int row);
};

#endif
