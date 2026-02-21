#ifndef TIME_HPP
#define TIME_HPP

#include <tuple>

namespace Time {
  using HHMMSS = std::tuple<unsigned int, unsigned int, unsigned int>;
  HHMMSS get_current();
}

#endif
