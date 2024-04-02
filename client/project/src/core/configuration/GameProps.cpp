#include "GameProps.h"

namespace zw
{
  GameProps*
  GameProps::Get()
  {
    static GameProps instance;                  // Create singleton instance once
    return &instance;
  }
}