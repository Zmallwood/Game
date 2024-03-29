#include "Utilities.h"

namespace Zmallwood
{
  int
  Ticks()
  {
    static sf::Clock clock;                     // Create clock object once
    return clock.getElapsedTime().asMilliseconds();
  }

  int
  Hash(const std::string& text)
  {
    return std::hash<std::string>{}(text);      // Use default hash function on string
  }
}