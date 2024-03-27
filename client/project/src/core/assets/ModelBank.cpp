#include "ModelBank.h"

namespace Zmallwood
{
  ModelBank*
  ModelBank::Get()
  {
    static ModelBank instance;                  // Create singleton instance once
    return &instance;
  }
}