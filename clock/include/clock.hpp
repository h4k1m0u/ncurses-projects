#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ncurses.h>
#include <vector>

#include "digit.hpp"

class Clock {
public:
  Clock(int rows, int cols);
  WINDOW* create_window();
  void draw(WINDOW* window);

private:
  int m_x;
  int m_y;
  int m_rows;
  int m_cols;
  std::vector<Digit> m_digits;

  static constexpr int N_CHARS = 5;
  static constexpr size_t N_DIGITS = 10;

  std::vector<Digit> get_digits();
};

#endif // CLOCK_HPP
