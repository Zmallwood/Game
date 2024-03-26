#pragma once
#include "core/scenes_core/IScene.h"

namespace JoD {
    class MainMenuScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static MainMenuScene *Get();

       private:
        MainMenuScene();
    };
}