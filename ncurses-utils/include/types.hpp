#ifndef TYPES_PAIRS_HPP
#define TYPES_PAIRS_HPP

#include <unordered_map>

#include <stb-utils/types.hpp>

using ColorIndex = unsigned char;

using ColorsMap = std::unordered_map<ColorInt, ColorIndex>;

using Pair = int;
using PairsMap = std::unordered_map<ColorInt, Pair>;

#endif
