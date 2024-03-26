#pragma once
#include "core/scenes_core/IScene.h"

namespace Zmallwood {
    class NewGameScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static NewGameScene *Get();

       private:
        NewGameScene();
    };
}