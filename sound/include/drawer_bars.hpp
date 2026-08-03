#ifndef DRAWER_BARS_HPP
#define DRAWER_BARS_HPP

#include <ncurses.h>

#include "types.hpp"

namespace DrawerBar {
  void draw_mono(const Samples& samples, WINDOW* window, const SizeWindow& size_window);
  void draw_stereo(const Samples& samples, WINDOW* window, const SizeWindow& size_window);
}

#endif // DRAWER_BARS_HPP
