#include "Color.h"
#include "GLColor.h"

namespace Zmallwood {
    GLColor Color::ToGLColor() {
        return {r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
    }
}