#pragma once
#include "core/scenes_core/IScene.h"

namespace Funtasia {
    class WorldGenerationScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static WorldGenerationScene *Get();

       private:
        WorldGenerationScene();
    };
}