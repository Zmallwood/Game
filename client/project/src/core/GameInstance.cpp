#include "GameInstance.h"
#include "Engine.h"

namespace Zmallwood
{
  void
  GameInstance::Run()
  {
    auto e = Engine::Get();
    while (e->Running())                        // Main game loop 
    {
      e->HandleInput();
      e->Update();
      e->Render();
    }
  }
}