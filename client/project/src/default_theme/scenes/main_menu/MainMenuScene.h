#pragma once
#include "core/scenes_core/IScene.h"

namespace Zmallwood {
    class MainMenuScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static MainMenuScene *Get();

       private:
        MainMenuScene();
    };
}