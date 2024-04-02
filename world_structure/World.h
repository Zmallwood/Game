#pragma once

namespace zw
{
  class WorldArea;

  class World
  {
  public:
    auto WorldArea() { return m_worldArea; }
    static World* Get();

  private:
    World();

    std::shared_ptr<zw::WorldArea> m_worldArea;
  };
}