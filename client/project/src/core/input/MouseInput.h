#pragma once
#include "MouseButton.h"

namespace Zmallwood {
    class MouseInput {
       public:
        void OnMousePress(sf::Mouse::Button button);
        void OnMouseRelease(sf::Mouse::Button button);
        int MouseWheelDeltaPickResult();
        bool AnyButtonPressed();
        auto &LeftButton() { return m_leftButton; }
        auto &RightButton() { return m_rightButton; }
        void AddMouseWheelDelta(int delta);

        static MouseInput *Get();

       private:
        MouseInput() = default;

        MouseButton m_leftButton;
        MouseButton m_rightButton;
        int m_mouseWheelDelta = 0;
    };
}