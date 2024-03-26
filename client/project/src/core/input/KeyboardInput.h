#pragma once

namespace JoD {
    class KeyboardInput {
       public:
        void OnKeyPress(sf::Keyboard::Key key);
        void OnKeyRelease(sf::Keyboard::Key key);
        bool AnyKeyIsPressed();
        static KeyboardInput *Get();

       private:
        KeyboardInput() = default;

        std::set<sf::Keyboard::Key> m_pressedKeys;
    };
}