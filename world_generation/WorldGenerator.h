#pragma once

namespace zw
{
  class WorldGenerator
  {
  public:
    void GenerateWorld();
    static WorldGenerator* Get();

  private:
    WorldGenerator() = default;
  };
}