#include "GenerateElevation.h"
#include "../world_structure/WorldArea.h"
#include "../world_structure/Tile.h"

namespace Zmallwood {
  void GenerateElevation(std::shared_ptr<WorldArea> worldArea) {
    for (auto i = 0; i < 60; i++) {
      auto xCenter = rand() % worldArea->Width();
      auto yCenter = rand() % worldArea->Height();
      auto rMax = 3 + rand() % 12;

      for (auto r = rMax; r >= 0; r--) {
        for (auto y = yCenter - r; y <= yCenter + r; y++) {
          for (auto x = xCenter - r; x <= xCenter + r; x++) {
            if (!worldArea->ValidCoordinate({.x = x, .y = y})) {
              continue;
            }

            {
              auto dx = x - xCenter;
              auto dy = y - yCenter;

              if (dx * dx + dy * dy <= r * r) {
                if (!worldArea->GetTile({.x = x, .y = y})->Water()) {
                  worldArea->GetTile({.x = x, .y = y})->AddElevation(0.4f);
                }
              }
            }
          }
        }
      }
    }
  }
}