#include "CalculateNormals.h"
#include "../world_structure/WorldArea.h"
#include "core/core_math/NormalsCalculation.h"

namespace Zmallwood {
  void CalculateNormals(std::shared_ptr<WorldArea> worldArea) {
    for (auto y = 0; y < worldArea->Height(); y++) {
      for (auto x = 0; x < worldArea->Width(); x++) {
        CalculateNormal(worldArea, {.x = x, .y = y});
      }
    }
  }
}