#include "AnimationBank.h"

namespace Zmallwood
{
  AnimationBank*
  AnimationBank::Get()
  {
    static AnimationBank instance;              // Create singleton instance once
    return &instance;
  }
}