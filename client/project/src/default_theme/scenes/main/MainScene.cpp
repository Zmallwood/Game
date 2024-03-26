#include "MainScene.h"

namespace Funtasia {
    void MainScene::Update() {

    }

    void MainScene::Render3D() {
        
    }

    MainScene *MainScene::Get() {
        static MainScene instance;
        return &instance;
    }
}