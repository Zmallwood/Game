#pragma once
#include "core/scenes_core/IScene.h"

namespace JoD {
    class MainScene : public IScene {
       public:
        void Update() override;
        void Render3D() override;
        static MainScene *Get();

       private:
        MainScene() = default;
    };
}