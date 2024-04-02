#include "PlayerRendering.h"
#include "core/Player.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/models_rendering/ModelRenderer.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/Tile.h"

namespace zw
{
  void RenderPlayer()
  {
    auto playerModel = "ActorPlayer";
    auto playerModelHash = Hash(playerModel);
    auto animName = "AnimActorRest";
    auto animNameHash = Hash(animName);
    auto pos = Player::Get()->Position().Multiply(GameProps::Get()->TileSize());
    auto rot = 0.0f;
    auto scale = 1.5f;
    auto worldArea = World::Get()->WorldArea();
    auto tile = worldArea->GetTile(Player::Get()->Position().GetXZ().ToIntPoint());
    auto elev = tile->Elevation()*GameProps::Get()->ElevationScale();
    pos.y = elev;
    ModelRenderer::Get()->DrawModel(playerModelHash, animNameHash, Ticks() * 2, pos, rot, scale);
  }
}