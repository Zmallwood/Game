#pragma once

namespace Zmallwood
{
  class WorldArea;

  class World
  {
  public:
    auto WorldArea() { return m_worldArea; }
    static World* Get();

  private:
    World();

    std::shared_ptr<Zmallwood::WorldArea> m_worldArea;
  };
}