#include "MainScene.h"
#include "sub_processes/world_view/WorldViewRenderer.h"

namespace Zmallwood {
    void MainScene::OnEnter() {
        WorldViewRenderer::Get()->Initialize();
    }

    void MainScene::Update() {
        WorldViewRenderer::Get()->UpdateCamera();
    }

    void MainScene::Render3D() {
        WorldViewRenderer::Get()->RenderWorldView();
    }

    MainScene *MainScene::Get() {
        static MainScene instance;
        return &instance;
    }
}