#pragma once
#include "core/scenes_core/IScene.h"

namespace Zmallwood
{
  class IntroScene : public IScene
  {
  public:
    void Update() override;
    void Render3D() override;
    static IntroScene* Get();

  private:
    IntroScene();

    tgui::RichTextLabel::Ptr m_startText;
  };
}