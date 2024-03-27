#include "RunNewGameInstance.h"
#include "core/GameInstance.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  void
  RunNewGameInstance()
  {
    GameProps::Get()->SetClearColor({ .r = 30, .g = 0, .b = 30 });

    GameInstance gameInstance;
    gameInstance.Run();
  }
}