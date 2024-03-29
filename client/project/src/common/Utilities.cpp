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

  std::string
  FileExtension(const std::string& absPath)
  {
    return absPath.substr(absPath.find_last_of('.') + 1);
  }

  std::string
  FilenameNoExtension(const std::string& absPath)
  {
    auto nameWithExt = absPath.substr(absPath.find_last_of('/') + 1);

    return nameWithExt.substr(0, nameWithExt.find_last_of('.'));
  }
}