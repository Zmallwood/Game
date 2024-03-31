#include "Player.h"

namespace Zmallwood
{
  void Player::MoveNorth()
  {
    m_position.z--;
  }

  void Player::MoveEast()
  {
    m_position.x++;
  }

  void Player::MoveSouth()
  {
    m_position.z++;
  }

  void Player::MoveWest()
  {
    m_position.x--;
  }

  Player* Player::Get()
  {
    static Player instance;
    return &instance;
  }
}