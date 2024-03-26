#include "World.h"
#include "WorldArea.h"

namespace Funtasia {
    World::World() : m_worldArea(std::make_shared<Funtasia::WorldArea>()) {}

    World *World::Get() {
        static World instance;
        return &instance;
    }
}