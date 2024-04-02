#pragma once

namespace zw
{
  class Graphics
  {
  public:
    void PresentCanvas();
    auto RenderWindow() { return m_renderWindow; }
    static Graphics* Get();

  private:
    Graphics();

    std::shared_ptr<sf::RenderWindow> m_renderWindow;
  };
}