#include "GameProps.h"

namespace Zmallwood
{
  GameProps*
  GameProps::Get()
  {
    static GameProps instance;                  // Create singleton instance once
    return &instance;
  }
}