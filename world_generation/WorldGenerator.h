#pragma once

namespace Funtasia {
    class WorldGenerator {
       public:
        void GenerateWorld();
        static WorldGenerator *Get();

       private:
        WorldGenerator() = default;
    };
}