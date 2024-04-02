#include "PlayerPositioning.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "core/Player.h"

namespace zw
{
  bool PlayerOnGoodLocation()
  {
    auto worldArea = World::Get()->WorldArea();
    auto playerPos = Player::Get()->Position().GetXZ().ToIntPoint();
    auto tile = worldArea->GetTile(playerPos);

    if (tile->Type() == Hash("TileWater"))
      return false;

    if (tile->Object() != nullptr)
      return false;

    return true;
  }

  void EnsureGoodPlayerPosition()
  {
    while (!PlayerOnGoodLocation())
    {
      Player::Get()->MoveToRandomLocation();
    }
  }
}