#include "RunNewGameInstance.h"
#include "core/GameInstance.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  void
  RunNewGameInstance()
  {
    GameProps::Get()->SetClearColor(            // Set GL clear color
      { .r = 30, .g = 0, .b = 30 });

    GameInstance gameInstance;                  // Create new game instance
    gameInstance.Run();                         // and run
  }
}