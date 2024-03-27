#pragma once

namespace Zmallwood
{
  class Graphics
  {
  public:
    auto RenderWindow() { return m_renderWindow; }
    static Graphics* Get();

  private:
    Graphics();

    std::shared_ptr<sf::RenderWindow> m_renderWindow;
  };
}