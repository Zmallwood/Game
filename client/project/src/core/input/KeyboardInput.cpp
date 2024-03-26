#include "KeyboardInput.h"

namespace Zmallwood {
    void KeyboardInput::OnKeyPress(sf::Keyboard::Key key) {
        m_pressedKeys.insert(key);
    }

    void KeyboardInput::OnKeyRelease(sf::Keyboard::Key key) {
        m_pressedKeys.erase(key);
    }

    bool KeyboardInput::AnyKeyIsPressed() {
        return m_pressedKeys.size() > 0;
    }

    KeyboardInput *KeyboardInput::Get() {
        static KeyboardInput instance;
        return &instance;
    }
}