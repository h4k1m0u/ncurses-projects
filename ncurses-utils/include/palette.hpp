#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <string>
#include <vector>

#include <stb-utils/color.hpp>

#include "types.hpp"

/**
 * Load palette of colors from "/usr/local/share/ncurses-utils/xterm-256color.dat"
 * Palette downloaded from ncurses source code to "<ncurses-utils>/colors/xterm-256.dat"
 * `make install` used to copy palette file to "$(prefix)/share/ncurses-utils/"
 */
class Palette {
public:
  Palette() = default;
  void load_colors();
  ColorIndex find_index_closest_color(const Color& color) const;

private:
  static constexpr int N_COLORS = 256;

  // predefined macros retrieved with: `echo | cpp -dM - -o -`
#if __ANDROID__
  inline static const std::string PATH_PALETTE = "/data/data/com.termux/files/usr/share/ncurses-utils/xterm-256color.dat";
#else
  inline static const std::string PATH_PALETTE = "/usr/local/share/ncurses-utils/xterm-256color.dat";
#endif

  std::vector<Color> m_colors;

  unsigned char extract_number(const std::string& line, size_t& i);
  void skip_non_digits(const std::string& line, size_t& i);
};

#endif // PALETTE_HPP
