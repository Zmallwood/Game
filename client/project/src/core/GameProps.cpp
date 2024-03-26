#include "GameProps.h"

namespace Funtasia {
    GameProps *GameProps::Get() {
        static GameProps instance;
        return &instance;
    }
}