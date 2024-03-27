#include "WorldGenerator.h"
#include "../world_structure/World.h"
#include "CalculateNormals.h"
#include "GenerateElevation.h"
#include "GenerateGrass.h"
#include "GenerateWater.h"

namespace Zmallwood
{
  void
  WorldGenerator::GenerateWorld()
  {
    auto worldArea = World::Get()->WorldArea();

    GenerateGrass(worldArea);
    GenerateWater(worldArea);
    GenerateElevation(worldArea);
    CalculateNormals(worldArea);
  }

  WorldGenerator*
  WorldGenerator::Get()
  {
    static WorldGenerator instance;
    return &instance;
  }
}