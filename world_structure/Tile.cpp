#include "Tile.h"

namespace Zmallwood
{
  void
  Tile::AddElevation(float delta)
  {
    m_elevation += delta;
  }
}