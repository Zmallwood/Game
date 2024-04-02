#include "ObjectsRendering.h"
#include "../../../world_structure/Object.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "core/assets/AnimationBank.h"
#include "core/assets/ModelBank.h"
#include "core/assets/animation_structure/Animator.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/models_rendering/ModelRenderer.h"

namespace zw
{
  void RenderObjects()
  {
    auto worldArea = World::Get()->WorldArea();
    auto tileSize = GameProps::Get()->TileSize();

    for (auto y = 0; y < worldArea->Height(); y++)
    {
      for (auto x = 0; x < worldArea->Width(); x++)
      {
        auto pos = Point3F{ x * tileSize + tileSize / 2.0f,
                            //CalcTileAverageElevation(coord, currMapLocation.Translate(dLocX, dLocY)),
                            0.0f,
                            y * tileSize + tileSize / 2.0f };
        auto modelRotation = 0.0f;
        auto modelScaling = 6.0f;
        auto object = worldArea->GetTile({ .x = x, .y = y })->Object();
        if (object)
        {
          auto objectType = object->Type();
          auto objectName = ModelBank::Get()->GetModelName(objectType);
          auto animName = "Anim" + objectName;
          auto animNameHash = Hash(animName);
          auto animator = AnimationBank::Get()->GetAnimator(animNameHash, objectType);

          if (animator != nullptr)
          {
            animator->SetCurrentTime((Ticks() + (x + y) * 1311));
          }
          auto objectTile = worldArea->GetTile({ .x = x, .y = y });
          auto elev = objectTile->Elevation() * GameProps::Get()->ElevationScale();
          auto objectElev = elev;
          pos.y = objectElev;
          ModelRenderer::Get()->DrawModel(
            objectType, animNameHash, Ticks() + x * y * 10, pos, modelRotation, modelScaling);
        }
      }
    }
  }
}