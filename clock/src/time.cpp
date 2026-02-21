#include <chrono>

#include "time.hpp"

Time::HHMMSS Time::get_current() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* tm = std::localtime(&time);
  return std::make_tuple(tm->tm_hour, tm->tm_min, tm->tm_sec);
}
