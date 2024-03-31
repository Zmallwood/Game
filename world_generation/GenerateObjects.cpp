#include "GenerateObjects.h"
#include "../world_structure/Object.h"
#include "../world_structure/Tile.h"
#include "../world_structure/WorldArea.h"

namespace Zmallwood
{
  void GenerateObjects(std::shared_ptr<WorldArea> worldArea)
  {
      auto contentScaling = worldArea->Width() * worldArea->Height() / 100.0f / 100.0f;
    {
      auto numTree1s = 600 * contentScaling;

      for (auto i = 0; i < numTree1s; i++)
      {
        auto x = rand() % worldArea->Width();
        auto y = rand() % worldArea->Height();

        auto tile = worldArea->GetTile({ .x = x, .y = y });
        auto tileType = tile->Type();
        if (tileType == Hash("TileGrass"))
        {
          tile->SetObject(std::make_shared<Object>("ObjectTree1"));
        }
      }
    }
  }
}