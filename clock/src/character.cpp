#include <stdexcept>

#include "character.hpp"

Character::Character(const std::string& path_image):
  Sprite(path_image)
{
  if (m_image.n_channels != N_CHANNELS || m_image.width != WIDTH || m_image.height != HEIGHT) {
    throw std::runtime_error("Invalid image (wrong size or # of channels)");
  }
}
