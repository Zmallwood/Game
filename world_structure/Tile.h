#pragma once

namespace Zmallwood {
  class Tile {
   public:
    void SetGround(const std::string &text);
    void AddElevation(float delta);
    auto Color() { return m_color; }
    void SetColor(Zmallwood::Color value) { m_color = value; }
    auto Elevation() { return m_elevation; }
    auto Water() { return m_water; }
    void SetWater(bool value) { m_water = value; }
    auto Normal() { return m_normal; }
    void SetNormal(Point3F value) { m_normal = value; }

   private:
    Zmallwood::Color m_color;
    float m_elevation = 0.0f;
    bool m_water = false;
    Point3F m_normal = {.x = 0.0f, .y = 1.0f, .z = 0.0f};
  };
}