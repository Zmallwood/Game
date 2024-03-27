#include "GameInstance.h"
#include "Engine.h"

namespace Zmallwood
{
  void
  GameInstance::Run()
  {
    auto e = Engine::Get();
    while (e->Running())
    {
      e->HandleInput();
      e->Update();
      e->Render();
    }
  }
}