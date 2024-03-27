#pragma once

namespace Zmallwood {
  class Player {
   public:
    auto Position() { return m_position; }
    static Player *Get();

   private:
    Player() = default;

    Point3F m_position = {.x = 50.0f, .y = 0.0f, .z = 50.0f};
  };
}