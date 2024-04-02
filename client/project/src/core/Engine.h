#pragma once

namespace zw
{
  class Engine
  {
  public:
    void HandleInput();
    void Update();
    void Render();
    auto Running() { return m_running; }
    void SetRunning(bool value) { m_running = value; }
    static Engine* Get();

  private:
    Engine();

    bool m_running = true;
  };
}