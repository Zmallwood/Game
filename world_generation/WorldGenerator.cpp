#include "WorldGenerator.h"
#include "../world_structure/World.h"
#include "GenerateGrass.h"

namespace Zmallwood {
    void WorldGenerator::GenerateWorld() {
        auto worldArea = World::Get()->WorldArea();

        GenerateGrass(worldArea);
    }

    WorldGenerator *WorldGenerator::Get() {
        static WorldGenerator instance;
        return &instance;
    }
}