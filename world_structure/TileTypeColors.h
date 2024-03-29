#pragma once

namespace Zmallwood {
  inline static std::map<int, Color> k_tileTypeColors = 
  {
   {Hash("TileGrass"), Color {.r = 0, .g = 200, .b = 0}}, 
   {Hash("TileWater"), Color {.r = 0, .g = 150, .b = 255}}
  };
}