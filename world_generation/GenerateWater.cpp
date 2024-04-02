#include "../world_structure/Tile.h"
#include "../world_structure/WorldArea.h"
#include "GenerateWater.h"

namespace zw
{
  void GenerateWater(std::shared_ptr<WorldArea> worldArea)
  {
    auto contentScaling = worldArea->Width() * worldArea->Height() / 100.0f / 100.0f;

    for (auto i = 0; i < 15 * contentScaling; i++)
    {
      auto xCenter = rand() % worldArea->Width();
      auto yCenter = rand() % worldArea->Height();
      auto r = 3 + rand() % 13;

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
              worldArea->GetTile({ .x = x, .y = y })->SetType("TileWater");
            }
          }
        }
      }
    }
  }
}