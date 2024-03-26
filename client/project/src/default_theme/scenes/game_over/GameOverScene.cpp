#include "GameOverScene.h"

namespace Zmallwood {
    void GameOverScene::Update() {

    }

    void GameOverScene::Render3D() {
        
    }

    GameOverScene *GameOverScene::Get() {
        static GameOverScene instance;
        return &instance;
    }
}