#pragma once

namespace zw
{
  class Tile;

  class WorldArea
  {
  public:
    WorldArea();
    int Width();
    int Height();
    std::shared_ptr<Tile> GetTile(Point coordinate);
    bool ValidCoordinate(Point coordinate);

  private:
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
  };
}