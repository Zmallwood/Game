#include "GenerateElevation.h"
#include "../world_structure/Tile.h"
#include "../world_structure/WorldArea.h"

namespace zw
{
  void GenerateElevation(std::shared_ptr<WorldArea> worldArea)
  {
    auto contentScaling = worldArea->Width() * worldArea->Height() / 100.0f / 100.0f;

    for (auto i = 0; i < 60*contentScaling; i++)
    {
      auto xCenter = rand() % worldArea->Width();
      auto yCenter = rand() % worldArea->Height();
      auto rMax = 3 + rand() % 18;

      for (auto r = rMax; r >= 0; r--)
      {
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
                if (worldArea->GetTile({ .x = x, .y = y })->Type() != Hash("TileWater") &&
                    (x == 0 || worldArea->GetTile({ .x = x - 1, .y = y })->Type() != Hash("TileWater")) &&
                    (y == 0 || worldArea->GetTile({ .x = x, .y = y - 1 })->Type() != Hash("TileWater")) &&
                    ((x == 0 || y == 0) ||
                     worldArea->GetTile({ .x = x - 1, .y = y - 1 })->Type() != Hash("TileWater")))
                {
                  worldArea->GetTile({ .x = x, .y = y })->AddElevation(1.4f);
                }
              }
            }
          }
        }
      }
    }
  }
}