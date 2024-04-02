#include "KeyboardInput.h"

namespace zw
{
  void KeyboardInput::OnKeyPress(sf::Keyboard::Key key)
  {
    m_pressedKeys.insert(key);                  // Store pressed key to the set
  }

  void KeyboardInput::OnKeyRelease(sf::Keyboard::Key key)
  {
    m_pressedKeys.erase(key);                   // Remove the released key from the set
  }

  bool KeyboardInput::AnyKeyIsPressed()
  {
    return m_pressedKeys.size() > 0;            // Return true if not empty
  }

  bool KeyboardInput::KeyIsPressed(sf::Keyboard::Key key)
  {
    return m_pressedKeys.contains(key);
  }

  KeyboardInput* KeyboardInput::Get()
  {
    static KeyboardInput instance;              // Create singleton instance once
    return &instance;
  }
}