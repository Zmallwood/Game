#include "ModelBank.h"

namespace Zmallwood
{
  ModelBank*
  ModelBank::Get()
  {
    static ModelBank instance;
    return &instance;
  }
}