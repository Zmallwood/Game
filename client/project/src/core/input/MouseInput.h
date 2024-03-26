#pragma once
#include "MouseButton.h"

namespace Funtasia {
    class MouseInput {
       public:
        void OnMousePress(sf::Mouse::Button button);
        void OnMouseRelease(sf::Mouse::Button button);
        bool AnyButtonPressed();
        auto &LeftButton() { return m_leftButton; }
        auto &RightButton() { return m_rightButton; }
        static MouseInput *Get();

       private:
        MouseInput() = default;

        MouseButton m_leftButton;
        MouseButton m_rightButton;
    };
}