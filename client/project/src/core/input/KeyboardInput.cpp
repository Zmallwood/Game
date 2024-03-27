#include "KeyboardInput.h"

namespace Zmallwood
{
  void
  KeyboardInput::OnKeyPress(sf::Keyboard::Key key)
  {
    m_pressedKeys.insert(key);                  // Store pressed key to the set
  }

  void
  KeyboardInput::OnKeyRelease(sf::Keyboard::Key key)
  {
    m_pressedKeys.erase(key);                   // Remove the released key from the set
  }

  bool
  KeyboardInput::AnyKeyIsPressed()
  {
    return m_pressedKeys.size() > 0;            // Return true if not empty
  }

  KeyboardInput*
  KeyboardInput::Get()
  {
    static KeyboardInput instance;              // Create singleton instance once
    return &instance;
  }
}