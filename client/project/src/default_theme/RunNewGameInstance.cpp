#include "RunNewGameInstance.h"
#include "core/GameInstance.h"
#include "core/configuration/GameProps.h"

namespace zw
{
  void
  RunNewGameInstance()
  {
    GameProps::Get()->SetClearColor(            // Set GL clear color
      { .r = 0, .g = 0, .b = 0 });

    GameInstance gameInstance;                  // Create new game instance
    gameInstance.Run();                         // and run
  }
}