#include "PlayerRendering.h"
#include "core/Player.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/models_rendering/ModelRenderer.h"

namespace zw
{
  void
  RenderPlayer()
  {
    auto playerModel = "ActorPlayer";
    auto playerModelHash = Hash(playerModel);
    auto animName = "AnimActorRest";
    auto animNameHash = Hash(animName);
    auto pos = Player::Get()->Position().Multiply(GameProps::Get()->TileSize());
    auto rot = 0.0f;
    auto scale = 1.5f;
    ModelRenderer::Get()->DrawModel(
      playerModelHash, animNameHash, Ticks() * 2, pos, rot, scale);
  }
}