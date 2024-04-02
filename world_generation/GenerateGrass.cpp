#include "GenerateGrass.h"
#include "../world_structure/Tile.h"
#include "../world_structure/WorldArea.h"

namespace zw
{
  void
  GenerateGrass(std::shared_ptr<WorldArea> worldArea)
  {
    for (auto y = 0; y < worldArea->Height(); y++)
    {
      for (auto x = 0; x < worldArea->Width(); x++)
      {
        auto colorGrass = Color{ .r = 0, .g = 200, .b = 0 };
        worldArea->GetTile({ .x = x, .y = y })->SetType("TileGrass");
      }
    }
  }
}