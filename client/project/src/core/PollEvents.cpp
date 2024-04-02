#include "PollEvents.h"
#include "Engine.h"
#include "Graphics.h"
#include "input/KeyboardInput.h"
#include "input/MouseInput.h"
#include "scenes_core/SceneManager.h"

namespace zw
{
  void
  PollEvents()
  {
    auto renderWindow = Graphics::Get()->RenderWindow();
    {
      sf::Event event;
      while (renderWindow->pollEvent(event))
      {
        SceneManager::Get()->HandleEventCurrentScene(event);

        switch (event.type)
        {
          case sf::Event::Closed:
            Engine::Get()->SetRunning(false);
            break;
          case sf::Event::KeyPressed:
            KeyboardInput::Get()->OnKeyPress(event.key.code);
            break;
          case sf::Event::KeyReleased:
            KeyboardInput::Get()->OnKeyRelease(event.key.code);
            break;
          case sf::Event::MouseButtonPressed:
            MouseInput::Get()->OnMousePress(event.mouseButton.button);
            break;
          case sf::Event::MouseButtonReleased:
            MouseInput::Get()->OnMouseRelease(event.mouseButton.button);
            break;
          case sf::Event::MouseWheelScrolled:
            MouseInput::Get()->AddMouseWheelDelta(event.mouseWheelScroll.delta);
            break;
        }
      }
    }
  }
}