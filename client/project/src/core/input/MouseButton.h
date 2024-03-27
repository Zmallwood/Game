#pragma once

namespace Zmallwood {
  class MouseButton {
   public:
    void OnPress();
    void OnRelease();
    auto Pressed() { return m_pressed; }

   private:
    bool m_pressed = false;
  };
}