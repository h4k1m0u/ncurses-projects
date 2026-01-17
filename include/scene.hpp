#ifndef SCENE_HPP
#define SCENE_HPP

#include <random>
#include <ncurses.h>

#include "colors.hpp"

class Scene {
public:
  Scene(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars, const std::vector<ColorPair>& colors_pairs_mario);

private:
  static constexpr int MAX_N_STARS_ROW = 5;
  int m_rows;
  int m_cols;

  std::random_device m_seed;
  std::mt19937 m_generator;
  std::uniform_int_distribution<int> m_uniform_col;
  std::uniform_int_distribution<int> m_uniform_n_stars_row;

  /* cchar_t used to hold C wide-characters, wchar_t (to store unicode, e.g. emojis) */
  cchar_t m_block_full;
  cchar_t m_star;

  /* first: row, second: column */
  using Coord = std::pair<int, int>;
  inline static const std::vector<std::vector<Coord>> COORDS_MARIO = {
    // COORDS_RED
    {
      { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 },
      { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 },
      { 7, 6 },
      { 8, 6 }, { 8, 7 },
      { 9, 7 }, { 9, 8 }, { 9, 9 },
      { 10, 6 }, { 10, 7 }, { 10, 8 }, { 10, 9 },
      { 11, 6 }, { 11, 7 }, { 11, 8 }, { 11, 9 },
      { 12, 5 }, { 12, 6 }, { 12, 7 }, { 12, 8 }, { 12, 9 },
      { 13, 4 }, { 13, 5 }, { 13, 6 }, { 13, 7 }, { 13, 8 },
    },
    // COORDS_YELLOW
    {
      { 2, 6 }, { 2, 7 }, { 2, 9 },
      { 3, 3 }, { 3, 5 }, { 3, 6 }, { 3, 7 }, { 3, 9 }, { 3, 10 }, { 3, 11 },
      { 4, 3 }, { 4, 6 }, { 4, 7 }, { 4, 8 }, { 4, 10 }, { 4, 11 }, { 4, 12 },
      { 5, 4 }, { 5, 5 }, { 5, 6 }, { 5, 7 },
      { 6, 4 }, { 6, 5 }, { 6, 6 }, { 6, 7 }, { 6, 8 }, { 6, 9 }, { 6, 10 },
      { 9, 6 },
      { 10, 3 }, { 10, 4 }, { 10, 5 },
      { 11, 3 }, { 11, 4 }, { 11, 5 },
      { 12, 3 }, { 12, 4 },
    },
    // COORDS_BLACK
    {
      { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 8},
      { 3, 2 }, { 3, 4 }, { 3, 8 },
      { 4, 2 }, { 4, 4 }, { 4, 5 }, { 4, 9 },
      { 5, 2 }, { 5, 3 }, { 5, 8 }, { 5, 9 }, { 5, 10 }, { 5, 11 },
      { 7, 4 }, { 7, 5 }, { 7, 7 }, { 7, 8 },
      { 8, 3 }, { 8, 4 }, { 8, 5 }, { 8, 8 }, { 8, 9 },
      { 9, 3 }, { 9, 4 }, { 9, 5 },
      { 14, 4 }, { 14, 5 }, { 14, 6 }, { 14, 7 },
      { 15, 4 }, { 15, 5 }, { 15, 6 }, { 15, 7 }, { 15, 8 },
    },
  };

  void draw_grass(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass);
  void draw_sky(WINDOW* window, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars);
  void draw_stars_row(WINDOW* window, int row);
  void draw_mario(WINDOW* window, const std::vector<ColorPair>& colors_pairs_mario);
};

#endif
