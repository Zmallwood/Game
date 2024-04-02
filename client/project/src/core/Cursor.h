#pragma once

namespace Zmallwood
{
  class Cursor
  {
  public:
    void Initialize();
    void Render();
    static Cursor* Get();

  private:
    sf::Texture m_texCursorDefault;
    std::shared_ptr<sf::Sprite> m_sprCursorDefault;
    const float k_cursorSize = 2.0f;
  };
}