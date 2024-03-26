#include "MouseButton.h"

namespace JoD {
    void MouseButton::OnPress() {
        m_pressed = true;
    }

    void MouseButton::OnRelease() {
        m_pressed = false;
    }
}