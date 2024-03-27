#include "MainScene.h"
#include "sub_processes/world_view/WorldViewRenderer.h"
#include "sub_processes/CameraZooming.h"
#include "sub_processes/FPSMeasuring.h"

namespace Zmallwood {
  MainScene::MainScene() {
    {
      auto label = tgui::Label::create();
      label->getRenderer()->setTextColor(tgui::Color::White);
      label->setPosition("90%", "10%");
      GUI()->add(label, "lblFPS");
    }
  }

  void MainScene::OnEnter() {
    WorldViewRenderer::Get()->Initialize();
  }

  void MainScene::Update() {
    UpdateCameraZooming();
    UpdateFPSMeasuring();
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