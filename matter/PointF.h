#pragma once
#include "Point.h"

namespace Zmallwood {
    class PointF {
       public:
        PointF Translate(float dx, float dy) const { return {x + dx, y + dy}; }
        Point ToIntPoint(void) const {
            return {static_cast<int>(x), static_cast<int>(y)};
        }

        float x = 0.0f;
        float y = 0.0f;
    };
}