#include "WorldGenerator.h"
#include "../world_structure/World.h"
#include "CalculateNormals.h"
#include "GenerateElevation.h"
#include "GenerateGrass.h"
#include "GenerateObjects.h"
#include "GenerateRock.h"
#include "GenerateWater.h"

namespace zw
{
  void WorldGenerator::GenerateWorld()
  {
    auto worldArea = World::Get()->WorldArea();

    GenerateGrass(worldArea);
    GenerateWater(worldArea);
    GenerateElevation(worldArea);
    GenerateRock(worldArea);
    GenerateObjects(worldArea);
    CalculateNormals(worldArea);
  }

  WorldGenerator* WorldGenerator::Get()
  {
    static WorldGenerator instance;
    return &instance;
  }
}