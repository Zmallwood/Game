#pragma once
#include "core/scenes_core/IScene.h"

namespace Zmallwood {
    class GameOverScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static GameOverScene *Get();

       private:
        GameOverScene() = default;
    };
}