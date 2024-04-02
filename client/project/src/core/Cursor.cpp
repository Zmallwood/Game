#include "Cursor.h"
#include "Graphics.h"

namespace Zmallwood
{
  void Cursor::Initialize()
  {
    Graphics::Get()->RenderWindow()->setMouseCursorVisible(false);
    m_texCursorDefault.loadFromFile("resources/images/CursorDefault.png");
    m_sprCursorDefault = std::make_shared<sf::Sprite>(m_texCursorDefault);
    m_sprCursorDefault->setScale({ k_cursorSize, k_cursorSize });
  }

  void Cursor::Render()
  {
    m_sprCursorDefault->setPosition(
      static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Graphics::Get()->RenderWindow())));
    Graphics::Get()->RenderWindow()->draw(*m_sprCursorDefault);
  }

  Cursor* Cursor::Get()
  {
    static Cursor instance;
    return &instance;
  }
}
