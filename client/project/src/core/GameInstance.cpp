#include "GameInstance.h"
#include "Engine.h"

namespace Funtasia {
    void GameInstance::Run() {
        auto e = Engine::Get();
        while (e->Running()) {
            e->HandleInput();
            e->Update();
            e->Render();
        }
    }
}