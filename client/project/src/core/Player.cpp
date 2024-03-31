#include "Player.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"

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

  void Player::MoveToRandomLocation()
  {
    auto worldArea = World::Get()->WorldArea();
    m_position.x = rand() % worldArea->Width();
    m_position.z = rand() % worldArea->Height();
  }

  Player* Player::Get()
  {
    static Player instance;
    return &instance;
  }
}