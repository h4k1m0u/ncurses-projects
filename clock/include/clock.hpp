#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ncurses.h>
#include <vector>

#include "digit.hpp"

class Clock {
public:
  Clock(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window, int hours, int minutes);

private:
  int m_x;
  int m_y;
  int m_rows;
  int m_cols;
  std::vector<Digit> m_digits;

  static constexpr int N_CHARS = 5;
  static constexpr size_t N_DIGITS = 10;

  std::vector<Digit> get_digits();
  void draw_tens_and_units(WINDOW* window, size_t i_tens, size_t i_units, bool is_minutes);
  std::pair<unsigned int, unsigned int> get_digits_indexes(unsigned int x);
};

#endif // CLOCK_HPP
