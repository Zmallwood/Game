#include "World.h"
#include "WorldArea.h"

namespace zw
{
  World::World()
    : m_worldArea(std::make_shared<zw::WorldArea>())
  {
  }

  World*
  World::Get()
  {
    static World instance;
    return &instance;
  }
}