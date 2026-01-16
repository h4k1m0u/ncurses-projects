#include "scene.hpp"
#include "menu.hpp"
#include "symbols.hpp"
#include "frame.hpp"
#include <ncurses.h>

Scene::Scene(int rows, int cols):
  // ignore frame above/below & left/right
  m_rows(rows - 2*Frame::HEIGHT - Menu::HEIGHT),
  m_cols(cols - 2*Frame::HEIGHT),

  m_seed(std::random_device()),
  m_generator(m_seed()),

  // star unicode characters take two terminal cells
  // put them only in even cell indexes
  m_uniform_col(0, (m_cols - 2) % 2 == 0 ? m_cols - 2 : m_cols - 3),

  m_uniform_n_stars_row(0, MAX_N_STARS_ROW)
{
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);
  setcchar(&m_star, &Symbols::STAR, A_NORMAL, 0, NULL);
}

WINDOW* Scene::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, Frame::HEIGHT, Frame::HEIGHT);

  return win;
}

void Scene::draw(WINDOW* window, [[ maybe_unused ]] const std::vector<ColorPair>& colors_pairs_grass, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars) {
  draw_grass(window, colors_pairs_grass);
  draw_sky(window, colors_pairs_sky, colors_pairs_stars);
  wrefresh(window);
}

void Scene::draw_stars_row(WINDOW* window, int row) {
  int n_stars_row = m_uniform_n_stars_row(m_generator);

  // leave two terminal cells horizontally for each star (e.g. occupy only even positions)
  // otherwise draws empty boxes due to UB: https://stackoverflow.com/a/67430307/2228912
  for (int i = 0; i < n_stars_row; ++i) {
    int col;
    do {
      col = m_uniform_col(m_generator);
    } while (col % 2 == 1);

    mvwadd_wch(window, row, col, &m_star);
  }
}

void Scene::draw_grass(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass) {
  int n_colors = colors_pairs_grass.size();

  for (int col = 0; col < m_cols; ++col) {
    for (int i = 0; i < n_colors; i++) {
      int color_pair = colors_pairs_grass[i];
      wattr_on(window, COLOR_PAIR(color_pair), NULL);

      // pair of rows in same color, starting from those just above frame (grass)
      int row = (m_rows - 1) - 2*i;
      mvwadd_wch(window, row, col, &m_block_full);
      mvwadd_wch(window, row - 1, col, &m_block_full);

      wattr_off(window, COLOR_PAIR(color_pair), NULL);
    } // END ROWS
  } // END COLS
}

void Scene::draw_sky(WINDOW* window, const std::vector<ColorPair>& colors_pairs_sky, const std::vector<ColorPair>& colors_pairs_stars) {
  int n_colors = colors_pairs_sky.size();

  // start from top for night sky (shades of gray)
  for (int i = 0; i < n_colors; i++) {
    /* Blocks */
    int row = i;

    int color_pair_sky = colors_pairs_sky[i];
    wattr_on(window, COLOR_PAIR(color_pair_sky), NULL);

    for (int col = 0; col < m_cols; ++col) {
      mvwadd_wch(window, row, col, &m_block_full);
    } // END COLS

    /* Stars */
    wattr_off(window, COLOR_PAIR(color_pair_sky), NULL);

    int color_pair_star = colors_pairs_stars[i];
    wattr_on(window, COLOR_PAIR(color_pair_star), NULL);

    draw_stars_row(window, row);

    wattr_off(window, COLOR_PAIR(color_pair_star), NULL);
  } // END ROWS/COLORS
}
