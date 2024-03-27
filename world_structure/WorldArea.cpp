#include "WorldArea.h"
#include "Tile.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  WorldArea::WorldArea()
  {
    auto worldAreaWidth = GameProps::Get()->WorldAreaSize().w;
    auto worldAreaHeight = GameProps::Get()->WorldAreaSize().h;

    for (auto x = 0; x < worldAreaWidth; x++)
    {
      m_tiles.push_back(std::vector<std::shared_ptr<Tile>>());

      for (auto y = 0; y < worldAreaHeight; y++)
      {
        m_tiles.at(x).push_back(std::make_shared<Tile>());
      }
    }
  }

  int
  WorldArea::Width()
  {
    return m_tiles.size();
  }

  int
  WorldArea::Height()
  {
    if (m_tiles.size() >= 1)
    {
      return m_tiles.at(0).size();
    }
    else
    {
      return 0;
    }
  }

  std::shared_ptr<Tile>
  WorldArea::GetTile(Point coordinate)
  {
    if (ValidCoordinate(coordinate))
    {
      return m_tiles.at(coordinate.x).at(coordinate.y);
    }
    else
    {
      return nullptr;
    }
  }

  bool
  WorldArea::ValidCoordinate(Point coordinate)
  {
    return coordinate.x >= 0 && coordinate.y >= 0 && coordinate.x < Width() && coordinate.y < Height();
  }
}