#include "Color.h"
#include "ColorF.h"

namespace Zmallwood {
    ColorF Color::ToColorF() {
        return {r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
    }
}