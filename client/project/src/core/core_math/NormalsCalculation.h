#pragma once

namespace zw
{
  class WorldArea;

  /**
   * \brief Calculate normal for tile in provided worldArea at provided coordinate
   *
   * \param worldArea WorldArea containing the tile
   * 
   * \param coordinate Coordinate at which the tile is located
  */
  void CalculateNormal(std::shared_ptr<WorldArea> worldArea, Point coordinate);
}