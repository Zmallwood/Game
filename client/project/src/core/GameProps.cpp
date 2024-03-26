#include "GameProps.h"

namespace JoD {
    GameProps *GameProps::Get() {
        static GameProps instance;
        return &instance;
    }
}