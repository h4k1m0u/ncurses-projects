#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ncurses.h>
#include <vector>

#include "character.hpp"
#include "time.hpp"

class Clock {
public:
  Clock(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, const Time::HHMMSS& time);

private:
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;
  std::vector<Character> m_digits;
  Character m_colon;

  static constexpr size_t N_DIGITS = 10;
  static constexpr int PADDING = 1;

  std::vector<Character> get_digits();
  void draw_tens_and_units(WINDOW* window, size_t i_tens, size_t i_units, bool is_minutes);
  std::pair<unsigned int, unsigned int> get_digits_indexes(unsigned int x);
};

#endif // CLOCK_HPP
