#include "GenerateGrass.h"
#include "../world_structure/WorldArea.h"
#include "../world_structure/Tile.h"

namespace Zmallwood {
    void GenerateGrass(std::shared_ptr<WorldArea> worldArea) {
        for (auto y = 0; y < worldArea->Height(); y++) {
            for (auto x = 0; x < worldArea->Width(); x++) {
                worldArea->GetTile({.x = x, .y = y})->SetGround("GroundGrass");
                auto colorGrass = Color{.r = 0, .g = 200, .b = 0};
                worldArea->GetTile({.x = x, .y = y})->SetColor(colorGrass);
            }
        }
    }
}