#include "TileLayerRendering.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "core/rendering/ground_rendering/TileRenderer.h"

namespace zw
{
  void RenderTileLayers()
  {

    auto worldArea = World::Get()->WorldArea();

    for (auto y = 0; y < worldArea->Height(); y++)
    {
      for (auto x = 0; x < worldArea->Width(); x++)
      {
        auto tile = worldArea->GetTile({ .x = x, .y = y });

        if (tile->Type() == Hash("TileWater"))
        {
          auto animIndex = ((Ticks() + x * y * 10) % 1200) / 400;

          auto imgName = "TileLayerWater" + std::to_string(animIndex);
          auto drawID = tile->DrawID();


          TileRenderer::Get()->DrawTile(imgName, drawID);
        }
      }
    }
  }
}