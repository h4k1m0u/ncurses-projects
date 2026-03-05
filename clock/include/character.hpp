#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <ncurses.h>
#include <string>

#include <ncurses-utils/sprite.hpp>

/* Digits (0-9) and colon (:) */
class Character : public Sprite {
public:
  static constexpr int WIDTH = 5;
  static constexpr int HEIGHT = 7;
  static constexpr int N_CHANNELS = 1;

  Character() = default;
  Character(const std::string& path_image);
};

#endif // CHARACTER_HPP
