#pragma once

namespace Funtasia {
    class WorldArea;

    class World {
       public:
        auto WorldArea() { return m_worldArea; }
        static World *Get();

       private:
        World();

        std::shared_ptr<Funtasia::WorldArea> m_worldArea;
    };
}