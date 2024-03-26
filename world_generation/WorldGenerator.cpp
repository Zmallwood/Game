#include "WorldGenerator.h"

namespace Funtasia {
    void WorldGenerator::GenerateWorld() {
        
    }

    WorldGenerator *WorldGenerator::Get() {
        static WorldGenerator instance;
        return &instance;
    }
}