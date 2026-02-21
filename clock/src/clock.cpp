#include "clock.hpp"
#include "digit.hpp"

Clock::Clock(int rows, int cols):
  m_x(0),
  m_y(0),
  m_rows(rows),
  m_cols(cols),

  m_digits(get_digits())
{
}

WINDOW* Clock::create_window() {
  WINDOW* win = newwin(0, 0, 0, 0);

  return win;
}

std::vector<Digit> Clock::get_digits() {
  constexpr size_t N_DIGITS = 10;
  std::vector<Digit> digits(N_DIGITS);

  for (size_t i = 0; i < N_DIGITS; ++i) {
    std::string path_image = "images/" + std::to_string(i) + ".png";
    digits[i] = Digit(path_image);
  }

  return digits;
}

void Clock::draw(WINDOW* window) {
  for (size_t i = 0; i <= N_DIGITS; ++i) {
    const Digit& digit = m_digits[i];
    int row_offset = 0;
    int col_offset = i * Digit::WIDTH_DIGIT;

    digit.draw(window, row_offset, col_offset);
  }

  wrefresh(window);
}
