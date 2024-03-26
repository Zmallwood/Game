#include "MainScene.h"

namespace JoD {
    void MainScene::Update() {

    }

    void MainScene::Render3D() {
        
    }

    MainScene *MainScene::Get() {
        static MainScene instance;
        return &instance;
    }
}