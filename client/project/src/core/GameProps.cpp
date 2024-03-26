#include "GameProps.h"

namespace Zmallwood {
    GameProps *GameProps::Get() {
        static GameProps instance;
        return &instance;
    }
}