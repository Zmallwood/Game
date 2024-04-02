#include "KeyboardMovement.h"
#include "core/Player.h"
#include "core/input/KeyboardInput.h"

namespace zw
{
  void UpdateKeyboardMovement()
  {
    if (Ticks() > Player::Get()->TicksLastMove() + 1000 / Player::Get()->MovementSpeed())
    {
      auto wPressed = KeyboardInput::Get()->KeyIsPressed(sf::Keyboard::Key::W);
      auto aPressed = KeyboardInput::Get()->KeyIsPressed(sf::Keyboard::Key::A);
      auto sPressed = KeyboardInput::Get()->KeyIsPressed(sf::Keyboard::Key::S);
      auto dPressed = KeyboardInput::Get()->KeyIsPressed(sf::Keyboard::Key::D);

      if (wPressed || aPressed || sPressed || dPressed)
      {
        if (wPressed)
        {
          Player::Get()->MoveNorth();
        }
        if (aPressed)
        {
          Player::Get()->MoveWest();
        }
        if (sPressed)
        {
          Player::Get()->MoveSouth();
        }
        if (dPressed)
        {
          Player::Get()->MoveEast();
        }

        Player::Get()->SetTicksLastMove(Ticks());
      }
    }
  }
}