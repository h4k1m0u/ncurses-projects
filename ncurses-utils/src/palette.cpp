#include <cctype>
#include <fstream>
#include <stdexcept>

#include "palette.hpp"

Palette::Palette():
  m_colors(load_colors())
{
}

unsigned char Palette::extract_number(const std::string& line, size_t& i) {
  std::string str = "";

  while (std::isdigit(line[i])) {
    str += line[i];
    i++;
  }

  return std::stoi(str);
}

void Palette::skip_non_digits(const std::string& line, size_t& i) {
  while (!std::isdigit(line[i]))
    i++;
}

std::vector<Color> Palette::load_colors() {
  std::ifstream f(PATH_PALETTE);
  if (!f)
    throw std::runtime_error("Check that " + PATH_PALETTE + " exists");

  std::string line;
  std::vector<Color> colors(N_COLORS);

  while (std::getline(f, line)) {
    // ignore comments
    if (line.starts_with("#"))
      continue;

    // lines must start with a digit
    if (!std::isdigit(line[0]))
      continue;

    // parse color index
    size_t i = 0;
    unsigned char index = extract_number(line, i);

    // parse rgb components
    skip_non_digits(line, i);
    unsigned char red = extract_number(line, i);

    skip_non_digits(line, i);
    unsigned char green = extract_number(line, i);

    skip_non_digits(line, i);
    unsigned char blue = extract_number(line, i);

    Color color = { red, green, blue };
    colors[index] = color;
  }

  return colors;
}
