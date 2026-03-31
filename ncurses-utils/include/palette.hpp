#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <string>
#include <vector>

#include <stb-utils/color.hpp>

#include "types.hpp"

/**
 * Load palette of colors from "/usr/local/share/ncurses-utils/xterm-256color.dat"
 * Palette downloaded from ncurses source code to "<ncurses-utils>/colors/xterm-256.dat"
 * `make install` used to copy palette file to "/usr/local/share/ncurses-utils/"
 */
class Palette {
public:
  Palette() = default;
  void load_colors();
  ColorIndex find_index_closest_color(const Color& color) const;

private:
  static constexpr int N_COLORS = 256;
  inline static const std::string PATH_PALETTE = "/usr/local/share/ncurses-utils/xterm-256color.dat";

  std::vector<Color> m_colors;

  unsigned char extract_number(const std::string& line, size_t& i);
  void skip_non_digits(const std::string& line, size_t& i);
};

#endif // PALETTE_HPP
