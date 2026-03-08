#include <cctype>
#include <fstream>
#include <stdexcept>
#include <algorithm>

#include "palette.hpp"

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

void Palette::load_colors() {
  std::ifstream f(PATH_PALETTE);
  if (!f)
    throw std::runtime_error("Check that " + PATH_PALETTE + " exists");

  std::string line;
  m_colors.resize(N_COLORS);

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

    Color color(red, green, blue);
    m_colors[index] = color;
  }
}

ColorIndex Palette::find_index_closest_color(const Color& color_req) const {
  std::vector<float> distances2(N_COLORS);

  for (size_t i = 0; i < N_COLORS; ++i) {
    const Color& color = m_colors[i];
    float distance2 = color.distance2(color_req);

    if (distance2 == 0)
      return i;

    distances2[i] = distance2;
  }

  auto it_min = std::min_element(distances2.begin(), distances2.end());
  ColorIndex index_min = it_min - distances2.begin();
  return index_min;
}
