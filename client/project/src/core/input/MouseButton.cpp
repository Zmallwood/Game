#include "MouseButton.h"

namespace Zmallwood {
    void MouseButton::OnPress() {
        m_pressed = true;
    }

    void MouseButton::OnRelease() {
        m_pressed = false;
    }
}