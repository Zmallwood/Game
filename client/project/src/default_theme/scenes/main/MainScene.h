#pragma once
#include "core/scenes_core/IScene.h"

namespace zw
{
  class MainScene : public IScene
  {
  public:
    void OnEnter() override;
    void Update() override;
    void Render3D() override;
    static MainScene* Get();

  private:
    MainScene();
  };
}