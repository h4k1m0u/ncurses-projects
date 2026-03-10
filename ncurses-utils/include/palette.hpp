#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <string>
#include <vector>

#include <stb-utils/color.hpp>

#include "types.hpp"

/* Load platte of colors from /usr/share/ncurses-examples/xterm-256color.dat */
class Palette {
public:
  Palette() = default;
  void load_colors();
  ColorIndex find_index_closest_color(const Color& color) const;

private:
  static constexpr int N_COLORS = 256;
  inline static const std::string PATH_PALETTE = "/usr/share/ncurses-examples/xterm-256color.dat";

  std::vector<Color> m_colors;

  unsigned char extract_number(const std::string& line, size_t& i);
  void skip_non_digits(const std::string& line, size_t& i);
};

#endif // PALETTE_HPP
