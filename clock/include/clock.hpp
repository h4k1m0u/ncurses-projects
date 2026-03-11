#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <ncurses.h>
#include <array>

#include <ncurses-utils/sprite.hpp>

#include "constants.hpp"
#include "time.hpp"

using Digits = std::array<Sprite, Constants::N_DIGITS>;

class Clock {
public:
  Clock(int rows, int cols, const Digits& digits, const Sprite& colon);
  WINDOW* create_window();
  void draw(WINDOW* window, const Time::HHMMSS& time, const PairsMap& pairs_map);

private:
  int m_rows;
  int m_cols;
  int m_x;
  int m_y;
  Digits m_digits;
  Sprite m_colon;

  static constexpr size_t N_CHARACTERS = 5;
  static constexpr int PADDING = 1;

  void draw_tens_and_units(WINDOW* window, size_t i_tens, size_t i_units, bool is_minutes, const PairsMap& pairs_map);
  std::pair<unsigned int, unsigned int> get_digits_indexes(unsigned int x);
};

#endif // CLOCK_HPP
