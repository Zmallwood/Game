#include "../world_structure/Tile.h"
#include "../world_structure/WorldArea.h"
#include "GenerateGrass.h"

namespace Zmallwood
{
  void
  GenerateWater(std::shared_ptr<WorldArea> worldArea)
  {
    for (auto i = 0; i < 60; i++)
    {
      auto xCenter = rand() % worldArea->Width();
      auto yCenter = rand() % worldArea->Height();
      auto r = 3 + rand() % 7;

      for (auto y = yCenter - r; y <= yCenter + r; y++)
      {
        for (auto x = xCenter - r; x <= xCenter + r; x++)
        {
          if (!worldArea->ValidCoordinate({ .x = x, .y = y }))
          {
            continue;
          }

          {
            auto dx = x - xCenter;
            auto dy = y - yCenter;

            if (dx * dx + dy * dy <= r * r)
            {
              auto colorWater = Color{ .r = 0, .g = 150, .b = 255 };
              worldArea->GetTile({ .x = x, .y = y })->SetType("TileWater");
            }
          }
        }
      }
    }
  }
}