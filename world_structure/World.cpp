#include "World.h"
#include "WorldArea.h"

namespace Zmallwood
{
  World::World()
    : m_worldArea(std::make_shared<Zmallwood::WorldArea>())
  {
  }

  World*
  World::Get()
  {
    static World instance;
    return &instance;
  }
}