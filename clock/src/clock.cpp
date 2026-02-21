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

void Clock::draw(WINDOW* window, int hours, int minutes) {
  auto [ i_tens_hours, i_units_hours ] = get_digits_indexes(hours);
  auto [ i_tens_minutes, i_units_minutes ] = get_digits_indexes(minutes);

  draw_tens_and_units(window, i_tens_hours, i_units_hours, false);
  draw_tens_and_units(window, i_tens_minutes, i_units_minutes, true);

  wrefresh(window);
}

/* Draws two digits for hours (hh) or minutes (mm) (accord. to is_minutes) */
void Clock::draw_tens_and_units(WINDOW* window, size_t i_tens, size_t i_units, bool is_minutes) {
  const Digit& digit_tens = m_digits[i_tens];
  const Digit& digit_units = m_digits[i_units];
  int row_offset = is_minutes ? 2 * Digit::WIDTH_DIGIT : 0;

  digit_tens.draw(window, 0, row_offset);
  digit_units.draw(window, 0, row_offset + Digit::WIDTH_DIGIT);
}

/* @param x Hours or minutes */
std::pair<unsigned int, unsigned int> Clock::get_digits_indexes(unsigned int x) {
  int i_tens = x / 10;
  int i_units = x % 10;
  return std::make_pair(i_tens, i_units);
}
