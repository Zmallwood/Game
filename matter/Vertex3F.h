#pragma once
#include "Color.h"
#include "Point3F.h"
#include "PointF.h"

namespace zw
{
  class Vertex3F
  {
  public:
    Point3F position;
    ColorF color;
    PointF uv;
    Point3F normal;
  };
}