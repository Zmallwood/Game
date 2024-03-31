#pragma once

namespace Zmallwood
{
  /**
   * \brief Contains game properties for a game instance.
  */
  class GameProps
  {
  public:
    // Getters/Setters
    Color ClearColor() { return m_clearColor; }
    void SetClearColor(Color value) { m_clearColor = value; }
    Size WorldAreaSize() { return m_worldAreaSize; }
    void SetWorldAreaSize(Size value) { m_worldAreaSize = value; }
    float TileSize() { return m_tileSize; }
    
    /**
     * \brief Get singleton instance
     *
     * \return Singleton instance
    */
    static GameProps* Get();

  private:
   /**
    * \brief Private constructor to force use singleton
   */
    GameProps() = default;

    Color m_clearColor = { 0, 150, 255, 255 };     ///< Clear color used by OpenGL used every frame.
    Size m_worldAreaSize = { 100, 100 };        ///< Size in number of tiles for the world areas.
    float m_tileSize = 1.0f;                    ///< Size of a single tile in number of length units.
  };
}