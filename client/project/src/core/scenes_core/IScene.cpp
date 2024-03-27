#include "IScene.h"
#include "core/Graphics.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood {
  IScene::IScene() {
    m_gui = std::make_shared<tgui::Gui>(*Graphics::Get()->RenderWindow());
  }

  void IScene::Render() {
    {
      auto clearColor = GameProps::Get()->ClearColor().ToColorF();
      glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Render3D();

    {
      auto renderWindow = Graphics::Get()->RenderWindow();
      renderWindow->pushGLStates();
      renderWindow->resetGLStates();
      m_gui->draw();
      renderWindow->popGLStates();

      renderWindow->display();
    }
  }
}