#pragma once

namespace Zmallwood
{
  /**
   * \brief Contains game properties for a game instance.
  */
  class GameProps
  {
  public:
    auto ClearColor() { return m_clearColor; }
    void SetClearColor(Color value) { m_clearColor = value; }
    auto WorldAreaSize() { return m_worldAreaSize; }
    void SetWorldAreaSize(Size value) { m_worldAreaSize = value; }
    auto TileSize() { return m_tileSize; }
    static GameProps* Get();

  private:
   /**
    * \brief Private constructor to force use singleton
   */
    GameProps() = default;

    Color m_clearColor = { 0, 0, 20, 255 };     ///< Clear color used by OpenGL used every frame.
    Size m_worldAreaSize = { 100, 100 };        ///< Size in number of tiles for the world areas.
    float m_tileSize = 1.0f;                    ///< Size of a single tile in number of length units.
  };
}