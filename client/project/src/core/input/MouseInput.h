#pragma once
#include "MouseButton.h"

namespace Zmallwood
{
  /**
   * \brief Handles mouse input and provides easy access to it
  */
  class MouseInput
  {
  public:
    /**
     * \brief Called from event polling when a mouse button has been pressed down
     *
     * \param button Button that has been pressed, left or right
    */
    void OnMousePress(sf::Mouse::Button button);

    /**
     * \brief Called from event polling when a mouse button has been released
     * 
     * \param button Button that has been released, left or right
    */
    void OnMouseRelease(sf::Mouse::Button button);

    /**
     * \brief Returns delta motion of mouse wheel, and also resets the state
     *
     * \return Delta motion of mouse wheel
    */
    int MouseWheelDeltaPickResult();

    /**
     * \brief Tells if any of the mouse buttons is currently being pressed down
     * 
     * \return True if any of the mouse buttons is currently being pressed down, otherwise false
    */
    bool AnyButtonPressed();

    /**
     * \brief Adds delta value to the total mouse wheel motion delta, called from event polling
     *
     * \param delta Delta value to add
    */
    void AddMouseWheelDelta(int delta);

    // Getters/Setters
    auto& LeftButton() { return m_leftButton; }
    auto& RightButton() { return m_rightButton; }

    /**
     * \brief Gets singleton instance
     *
     * \return Singleton instance
    */
    static MouseInput* Get();

  private:
    /**
     * \brief Private constructor to force use singleton instance
    */
    MouseInput() = default;

    MouseButton m_leftButton;                   ///< Left mouse button
    MouseButton m_rightButton;                  ///< Right mouse button
    int m_mouseWheelDelta = 0;                  ///< Total motion delta of mouse wheel
  };
}