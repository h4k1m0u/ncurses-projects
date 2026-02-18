#include "background.hpp"
#include "colors.hpp"
#include "menu.hpp"
#include "symbols.hpp"
#include "frame.hpp"
#include <ncurses.h>
#include <stdexcept>

Background::Background(int rows, int cols):
  // ignore frame above/below & left/right
  m_rows(rows - 2*Frame::HEIGHT - Menu::HEIGHT),
  m_cols(cols - 2*Frame::WIDTH),

  m_seed(std::random_device()),
  m_generator(m_seed()),

  // star unicode characters take two terminal cells
  // put them only in even cell indexes
  m_uniform_col(0, (m_cols - 2) % 2 == 0 ? m_cols - 2 : m_cols - 3),

  m_uniform_n_stars_row(0, MAX_N_STARS_ROW),
  m_uniform_stars_symbols(0, N_STARS_SYMBOLS - 1)
{
  setcchar(&m_block_full, &Symbols::FULL_WCHAR, A_NORMAL, 0, NULL);

  setcchar(&m_stars[0], &Symbols::STAR_BLACK, A_NORMAL, 0, NULL);
  setcchar(&m_stars[1], &Symbols::STAR_WHITE, A_NORMAL, 0, NULL);
  setcchar(&m_stars[2], &Symbols::STAR_BLACK4, A_NORMAL, 0, NULL);
  setcchar(&m_stars[3], &Symbols::STAR_WHITE4, A_NORMAL, 0, NULL);
}

WINDOW* Background::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, Frame::HEIGHT, Frame::HEIGHT);

  return win;
}

void Background::draw(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass, const std::vector<ColorPair>& colors_pairs_stars) {
  draw_grass(window, colors_pairs_grass);
  draw_stars(window, colors_pairs_stars);
  wrefresh(window);
}

void Background::draw_stars_row(WINDOW* window, int row) {
  int n_stars_row = m_uniform_n_stars_row(m_generator);

  // leave two terminal cells horizontally for each star (e.g. occupy only even positions)
  // otherwise draws empty boxes due to UB: https://stackoverflow.com/a/67430307/2228912
  for (int i = 0; i < n_stars_row; ++i) {
    int col;
    do {
      col = m_uniform_col(m_generator);
    } while (col % 2 == 1);

    int i_star = m_uniform_stars_symbols(m_generator);
    cchar_t star = m_stars[i_star];
    mvwadd_wch(window, row, col, &star);
  }
}

void Background::draw_grass(WINDOW* window, const std::vector<ColorPair>& colors_pairs_grass) {
  if (2 * colors_pairs_grass.size() != HEIGHT_GRASS)
    throw std::runtime_error("Number of grass colors must be equal to 3");

  for (int col = 0; col < m_cols; ++col) {
    for (int i = 0; i < HEIGHT_GRASS; i++) {
      int color_pair = colors_pairs_grass[i / 2];
      wattr_on(window, COLOR_PAIR(color_pair), NULL);

      // pair of rows in same color, starting from those just above frame (grass)
      int row = (m_rows - 1) - i;
      mvwadd_wch(window, row, col, &m_block_full);
      // mvwadd_wch(window, row - 1, col, &m_block_full);

      wattr_off(window, COLOR_PAIR(color_pair), NULL);
    } // END ROWS
  } // END COLS
}

void Background::draw_stars(WINDOW* window, const std::vector<ColorPair>& colors_pairs_stars) {
  int n_colors = colors_pairs_stars.size();

  // start from top for night sky (shades of gray)
  for (int i = 0; i < n_colors; i++) {
    int color_pair_star = colors_pairs_stars[i];
    wattr_on(window, COLOR_PAIR(color_pair_star), NULL);

    int row = i;
    draw_stars_row(window, row);

    wattr_off(window, COLOR_PAIR(color_pair_star), NULL);
  } // END ROWS/COLORS
}
