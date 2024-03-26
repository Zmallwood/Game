#include "Utilities.h"

namespace Funtasia {
    int Ticks() {
        static sf::Clock clock;
        return clock.getElapsedTime().asMilliseconds();
    }

    int Hash(const std::string &text) {
        return std::hash<std::string>{}(text);
    }
}