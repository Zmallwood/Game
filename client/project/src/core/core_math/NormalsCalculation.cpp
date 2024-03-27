#include "NormalsCalculation.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/Tile.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood {
  void CalculateNormal(std::shared_ptr<WorldArea> worldArea, Point coordinate) {
    auto coord00 = coordinate;
    auto coord10 = coordinate.Translate(1, 0);
    auto coord01 = coordinate.Translate(0, 1);
    if (worldArea->ValidCoordinate(coord00)) {
      auto elev00 = worldArea->GetTile(coord00)->Elevation();
      auto elev10 = elev00;
      auto elev01 = elev00;
      if (worldArea->ValidCoordinate(coord10)) {
        elev10 = worldArea->GetTile(coord10)->Elevation();
      }
      if (worldArea->ValidCoordinate(coord01)) {
        elev01 = worldArea->GetTile(coord01)->Elevation();
      }

      auto tileSize = GameProps::Get()->TileSize();
      auto elevAmount = 1.0f;

      auto i = glm::vec3{coordinate.x * tileSize, elev00 * elevAmount,
                         coordinate.y * tileSize};
      auto i1 = glm::vec3{(coordinate.x + 1) * tileSize, elev10 * elevAmount,
                          coordinate.y * tileSize};
      auto i2 = glm::vec3{coordinate.x * tileSize, elev01 * elevAmount,
                          (coordinate.y + 1) * tileSize};

      auto v1 = i1 - i;
      auto v2 = i2 - i;

      auto v3 = glm::cross(v1, v2);
      auto normal = glm::normalize(v3);
      worldArea->GetTile(coord00)->SetNormal(
          {.x = normal.x, .y = -normal.y, .z = normal.z});
    }
  }
}