#pragma once

namespace Funtasia {
    class Tile;

    class WorldArea {
       public:
        WorldArea();

       private:
        std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
    };
}