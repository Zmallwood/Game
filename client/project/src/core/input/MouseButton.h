#pragma once

namespace zw
{
  /**
   * \brief A single mouse button, left or right
  */
  class MouseButton
  {
  public:
    /**
     * \brief Called during event polling when button has been pressed down
    */
    void OnPress();

    /**
     * \brief Called during event polling when button has been released
    */
    void OnRelease();

    // Getters/Setters
    auto Pressed() { return m_pressed; }

  private:
    bool m_pressed = false;                     ///< Is button currently being pressed down
  };
}