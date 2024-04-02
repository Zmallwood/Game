#include "MainScene.h"
#include "sub_processes/CameraRotater.h"
#include "sub_processes/CameraZooming.h"
#include "sub_processes/FPSMeasuring.h"
#include "sub_processes/KeyboardMovement.h"
#include "sub_processes/PlayerPositioning.h"
#include "sub_processes/world_view/WorldViewRenderer.h"

namespace Zmallwood
{
  MainScene::MainScene()
  {
    {
      auto label = tgui::Label::create();
      label->getRenderer()->setTextColor(tgui::Color::White);
      label->setPosition("90%", "10%");
      GUI()->add(label, "lblFPS");
    }
  }

  void MainScene::OnEnter()
  {
    WorldViewRenderer::Get()->Initialize();
    EnsureGoodPlayerPosition();
  }

  void MainScene::Update()
  {
    UpdateKeyboardMovement();
    UpdateCameraZooming();
    CameraRotater::Get()->Update();
    UpdateFPSMeasuring();
    WorldViewRenderer::Get()->UpdateCamera();
  }

  void MainScene::Render3D()
  {
    WorldViewRenderer::Get()->RenderWorldView();
  }

  MainScene* MainScene::Get()
  {
    static MainScene instance;
    return &instance;
  }
}