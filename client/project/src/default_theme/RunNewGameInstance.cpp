#include "RunNewGameInstance.h"
#include "core/GameInstance.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  void
  RunNewGameInstance()
  {
    GameProps::Get()->SetClearColor(            // Set GL clear color
      { .r = 0, .g = 150, .b = 255 });

    GameInstance gameInstance;                  // Create new game instance
    gameInstance.Run();                         // and run
  }
}