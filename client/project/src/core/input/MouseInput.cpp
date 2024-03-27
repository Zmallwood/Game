#include "MouseInput.h"

namespace Zmallwood
{
  void
  MouseInput::OnMousePress(sf::Mouse::Button button)
  {
    switch (button)                             // Left or right mouse button pressed?
    {
      case sf::Mouse::Button::Left:
        m_leftButton.OnPress();                 // Forward the event to the left button
        break;
      case sf::Mouse::Button::Right:
        m_rightButton.OnPress();                // Forward the event to the right button
        break;
    }
  }

  void
  MouseInput::OnMouseRelease(sf::Mouse::Button button)
  {
    switch (button)                             // Left or right mouse button released?
    {
      case sf::Mouse::Button::Left:
        m_leftButton.OnRelease();               // Forward the event to the left button
        break;
      case sf::Mouse::Button::Right:
        m_rightButton.OnRelease();              // Forward the event to the right button
        break;
    }
  }

  bool
  MouseInput::AnyButtonPressed()
  {                                             // Check if either left or right button is pressed
    return m_leftButton.Pressed() || m_rightButton.Pressed();
  }

  int
  MouseInput::MouseWheelDeltaPickResult()
  {
    auto result = m_mouseWheelDelta;            // Save current delta value
    m_mouseWheelDelta = 0;                      // Reset internal delta value
    return result;                              // Return saved delta value
  }

  void
  MouseInput::AddMouseWheelDelta(int delta)
  {
    m_mouseWheelDelta += delta;                 // Add either positive or negative value
  }

  MouseInput*
  MouseInput::Get()
  {
    static MouseInput instance;                 // Create singleton instance once
    return &instance;
  }
}