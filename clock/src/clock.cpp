#include "clock.hpp"
#include "character.hpp"

Clock::Clock(int rows, int cols):
  // padding between tens & units for both hours & minutes
  m_rows(Image::HEIGHT),
  m_cols(5 * Image::HEIGHT + 2 * PADDING),
  m_x(cols / 2 - m_cols / 2),
  m_y(rows / 2 - m_rows / 2),

  m_digits(get_digits()),
  m_colon("images/colon.png")
{
}

WINDOW* Clock::create_window() {
  WINDOW* win = newwin(m_rows, m_cols, m_y, m_x);

  return win;
}

std::vector<Character> Clock::get_digits() {
  std::vector<Character> digits(N_DIGITS);

  for (size_t i = 0; i < N_DIGITS; ++i) {
    std::string path_image = "images/" + std::to_string(i) + ".png";
    digits[i] = Character(path_image);
  }

  return digits;
}

/* two digits for minutes + colon + two digits for minutes */
void Clock::draw(WINDOW* window, const Time::HHMMSS& time) {
  auto [ hours, minutes, seconds ] = time;
  auto [ i_tens_hours, i_units_hours ] = get_digits_indexes(hours);
  auto [ i_tens_minutes, i_units_minutes ] = get_digits_indexes(minutes);

  draw_tens_and_units(window, i_tens_hours, i_units_hours, false);
  if (seconds % 2 == 0)
    m_colon.draw(window, 0, 2 * Image::WIDTH + PADDING);
  draw_tens_and_units(window, i_tens_minutes, i_units_minutes, true);

  wrefresh(window);
}

/* Draws two digits for hours (hh) or minutes (mm) (accord. to is_minutes) */
void Clock::draw_tens_and_units(WINDOW* window, size_t i_tens, size_t i_units, bool is_minutes) {
  const Character& digit_tens = m_digits[i_tens];
  const Character& digit_units = m_digits[i_units];

  int col_offset_tens = is_minutes ? 3 * Image::WIDTH : 0;
  int col_offset_units = is_minutes ? 4 * Image::WIDTH : Image::WIDTH;

  // separate units from tens for both hours & minutes (due to font)
  int padding_tens = is_minutes ? PADDING : 0;
  int padding_units = is_minutes ? 2 * PADDING : PADDING;

  digit_tens.draw(window, 0, col_offset_tens + padding_tens);
  digit_units.draw(window, 0, col_offset_units + padding_units);
}

/* @param x Hours or minutes */
std::pair<unsigned int, unsigned int> Clock::get_digits_indexes(unsigned int x) {
  int i_tens = x / 10;
  int i_units = x % 10;
  return std::make_pair(i_tens, i_units);
}
