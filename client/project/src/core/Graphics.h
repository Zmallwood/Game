#pragma once

namespace zw
{
  class Graphics
  {
  public:
    void Start2DRendering();
    void Stop2DRendering();
    void PresentCanvas();
    auto RenderWindow() { return m_renderWindow; }
    static Graphics* Get();

  private:
    Graphics();

    std::shared_ptr<sf::RenderWindow> m_renderWindow;
  };
}