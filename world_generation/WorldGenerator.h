#pragma once

namespace Zmallwood
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