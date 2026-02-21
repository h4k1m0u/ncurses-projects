#ifndef NCURSES_UTILS_HPP
#define NCURSES_UTILS_HPP

#include <utility>

#include "ncurses.h"

namespace NcursesUtils {
  std::pair<int, int> init();
  void configure_input(WINDOW* window);
};

#endif
