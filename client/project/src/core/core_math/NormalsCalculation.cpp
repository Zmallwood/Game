#include "NormalsCalculation.h"
#include "../../../world_structure/Tile.h"
#include "../../../world_structure/WorldArea.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  void
  CalculateNormal(std::shared_ptr<WorldArea> worldArea, Point coordinate)
  {
    auto coord00 = coordinate;                  // North-west corner of the tile
    auto coord10 = coordinate.Translate(1, 0);  // North east corner of the tile
    auto coord01 = coordinate.Translate(0, 1);  // South west corner of the tile
    if (worldArea->ValidCoordinate(coord00))    // Is the northwest corner inside the map?
    {
      auto elev00 = worldArea->GetTile(coord00)->Elevation();
      auto elev10 = elev00;
      auto elev01 = elev00;
      if (worldArea->ValidCoordinate(coord10))  // Is the north east corner inside the map?
      {                                         // If so, read its elevation.
        elev10 = worldArea->GetTile(coord10)->Elevation();
      }
      if (worldArea->ValidCoordinate(coord01))  // Is the south west corner inside the map?
      {                                         // If so, read its elevation.
        elev01 = worldArea->GetTile(coord01)->Elevation();
      }

      auto tileSize = GameProps::Get()->TileSize();
      auto elevAmount = 1.0f;

      // Create 3 vertices between tree of the tile corners.
      auto i = glm::vec3{                       // North west corner
                          coordinate.x * tileSize,
                          elev00 * elevAmount,
                          coordinate.y * tileSize
      };
      auto i1 = glm::vec3{                      // North east corner
                           (coordinate.x + 1) * tileSize,
                           elev10 * elevAmount,
                           coordinate.y * tileSize
      };
      auto i2 = glm::vec3{                      // South west corner
                           coordinate.x * tileSize,
                           elev01 * elevAmount,
                           (coordinate.y + 1) * tileSize
      };

      auto v1 = i1 - i;                         // Vector from northwest to north east corner
      auto v2 = i2 - i;                         // Vector from northwest to south west corner

      auto v3 = glm::cross(v1, v2);             // Calculate cross product from the two vectors
      auto normal = glm::normalize(v3);

      // Set the normal to the calculated vector, but invert the y value
      worldArea->GetTile(coord00)->SetNormal({ .x = normal.x, .y = -normal.y, .z = normal.z });
    }
  }
}