#pragma once

namespace Zmallwood
{
  /**
   * \brief Handles keyboard input and provides easy reading of it
  */
  class KeyboardInput
  {
  public:
    /**
     * \brief Called from event polling when a key has been pressed down
     *
     * \param key Key that has been pressed down
    */
    void OnKeyPress(sf::Keyboard::Key key);

    /**
     * \brief Called from event polling when a key has been released
     *
     * \param key Key that has been released
    */
    void OnKeyRelease(sf::Keyboard::Key key);

    /**
     * \brief Tells if any key is currently being pressed down 
     * 
     * \return True if any key is currently being pressed down, otherwise false
    */
    bool AnyKeyIsPressed();
    
    bool KeyIsPressed(sf::Keyboard::Key key);

    /**
     * \brief Get singleton instance
     * 
     * \return Singleton instance
    */
    static KeyboardInput* Get();

  private:
    /**
     * \brief Private constructor to force use singleton
    */
    KeyboardInput() = default;

    std::set<sf::Keyboard::Key> m_pressedKeys;  ///< Keys currently being pressed down 
  };
}