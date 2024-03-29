#include "Tile.h"

namespace Zmallwood
{
  void Tile::SetType(const std::string& typeName) {
    m_type = Hash(typeName);
  }

  void
  Tile::AddElevation(float delta)
  {
    m_elevation += delta;
  }
}