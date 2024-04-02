#pragma once

namespace zw
{
  class Object;

  class Tile
  {
  public:
    auto Type() { return m_type; }
    void SetType(const std::string& typeName);
    void AddElevation(float delta);
    auto Elevation() { return m_elevation; }
    auto Normal() { return m_normal; }
    void SetNormal(Point3F value) { m_normal = value; }
    auto Object() { return m_object; }
    void SetObject(std::shared_ptr<zw::Object> value) { m_object = value; }
    auto& ColorAlteration() { return m_colorAlteration; }
    auto DrawID() { return m_drawID; }
    void SetDrawID(GLuint value) { m_drawID = value; }

  private:
    int m_type;
    float m_elevation = 0.0f;
    Point3F m_normal = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
    std::shared_ptr<zw::Object> m_object;
    Color m_colorAlteration = { .r = 0, .g = 0, .b = 0 };
    GLuint m_drawID = -1;
  };
}