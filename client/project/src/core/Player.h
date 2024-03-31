#pragma once

namespace Zmallwood
{
  class Player
  {
  public:
    void MoveNorth();
    void MoveEast();
    void MoveSouth();
    void MoveWest();
    void MoveToRandomLocation();
    auto Position() { return m_position; }
    auto TicksLastMove() { return m_ticksLastMove; }
    void SetTicksLastMove(int value) { m_ticksLastMove = value; }
    auto MovementSpeed() { return m_movementSpeed; }
    static Player* Get();

  private:
    Player() = default;

    Point3F m_position = { .x = 50.0f, .y = 0.0f, .z = 50.0f };
    int m_ticksLastMove = 0;
    float m_movementSpeed = 5.0f;
  };
}