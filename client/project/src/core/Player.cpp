#include "Player.h"

namespace Zmallwood
{
  Player*
  Player::Get()
  {
    static Player instance;
    return &instance;
  }
}