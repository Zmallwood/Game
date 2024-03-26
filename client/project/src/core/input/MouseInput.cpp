#include "MouseInput.h"

namespace Funtasia {
    void MouseInput::OnMousePress(sf::Mouse::Button button) {
        switch (button) {
            case sf::Mouse::Button::Left:
                m_leftButton.OnPress();
                break;
            case sf::Mouse::Button::Right:
                m_rightButton.OnPress();
                break;
        }
    }

    void MouseInput::OnMouseRelease(sf::Mouse::Button button) {
        switch (button) {
            case sf::Mouse::Button::Left:
                m_leftButton.OnRelease();
                break;
            case sf::Mouse::Button::Right:
                m_rightButton.OnRelease();
                break;
        }
    }

    bool MouseInput::AnyButtonPressed() {
        return m_leftButton.Pressed() || m_rightButton.Pressed();
    }

    MouseInput *MouseInput::Get() {
        static MouseInput instance;
        return &instance;
    }
}