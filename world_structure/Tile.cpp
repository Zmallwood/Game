#include "Tile.h"

namespace Zmallwood {
    void Tile::SetGround(const std::string &text) {
        m_ground = Hash(text);
    }
}