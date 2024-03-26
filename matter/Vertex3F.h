#pragma once
#include "PointF.h"
#include "Point3F.h"
#include "Color.h"

namespace Zmallwood {
    class Vertex3F {
       public:
        Point3F position;
        Color color;
        PointF uv;
        Point3F normal;
    };
}