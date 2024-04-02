#pragma once

namespace zw
{
  class Point3F
  {
  public:
    Point3F Translate(float dx, float dy, float dz) const
    {
      return { x + dx, y + dy, z + dz };         
    }
    Point3F Multiply(float k) const { return { x * k, y * k, z * k }; }
    PointF GetXZ(void) const { return { x, z }; }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
  };
}