#include "MouseButton.h"

namespace Funtasia {
    void MouseButton::OnPress() {
        m_pressed = true;
    }

    void MouseButton::OnRelease() {
        m_pressed = false;
    }
}