#include "AnimationBank.h"

namespace Zmallwood
{
  AnimationBank*
  AnimationBank::Get()
  {
    static AnimationBank instance;
    return &instance;
  }
}