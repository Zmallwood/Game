#pragma once
#include "Color.h"
#include "PointF.h"

namespace Zmallwood
{
  class Vertex2F
  {
  public:
    PointF position;
    Color color;
    PointF uv;
  };
}