#include "MainMenuScene.h"
#include "core/Engine.h"
#include "core/scenes_core/SceneManager.h"

namespace Zmallwood {
  MainMenuScene::MainMenuScene() {
    {
      auto button = tgui::Button::create("New game");
      button->setSize({140, 40});
      button->setPosition("(parent.width - width)/2", "30%");
      button->onPress([] { SceneManager::Get()->EnterScene("NewGameScene"); });
      GUI()->add(button);
    }
    {
      auto button = tgui::Button::create("Continue game");
      button->setSize({140, 40});
      button->setPosition("(parent.width - width)/2", "35%");
      button->onPress([] { std::cout << "Continue game\n"; });
      GUI()->add(button);
    }
    {
      auto button = tgui::Button::create("Exit");
      button->setSize({140, 40});
      button->setPosition("(parent.width - width)/2", "40%");
      button->onPress([] { Engine::Get()->SetRunning(false); });
      GUI()->add(button);
    }
  }

  void MainMenuScene::Update() {}

  void MainMenuScene::Render3D() {
    glTranslatef(0.f, 0.f, -200.f);

    {
      auto angle = Ticks() / 1000.0f;

      glRotatef(angle * 50, 1.f, 0.f, 0.f);
      glRotatef(angle * 30, 0.f, 1.f, 0.f);
      glRotatef(angle * 90, 0.f, 0.f, 1.f);
    }

    glBegin(GL_QUADS);

    glColor3i(0, 1, 1);
    glVertex3f(-50.f, -50.f, -50.f);
    glVertex3f(-50.f, 50.f, -50.f);
    glVertex3f(50.f, 50.f, -50.f);
    glVertex3f(50.f, -50.f, -50.f);

    glColor3f(0, 0, 1);
    glVertex3f(-50.f, -50.f, 50.f);
    glVertex3f(-50.f, 50.f, 50.f);
    glVertex3f(50.f, 50.f, 50.f);
    glVertex3f(50.f, -50.f, 50.f);

    glColor3f(1, 0, 1);
    glVertex3f(-50.f, -50.f, -50.f);
    glVertex3f(-50.f, 50.f, -50.f);
    glVertex3f(-50.f, 50.f, 50.f);
    glVertex3f(-50.f, -50.f, 50.f);

    glColor3f(0, 1, 0);
    glVertex3f(50.f, -50.f, -50.f);
    glVertex3f(50.f, 50.f, -50.f);
    glVertex3f(50.f, 50.f, 50.f);
    glVertex3f(50.f, -50.f, 50.f);

    glColor3f(1, 1, 0);
    glVertex3f(-50.f, -50.f, 50.f);
    glVertex3f(-50.f, -50.f, -50.f);
    glVertex3f(50.f, -50.f, -50.f);
    glVertex3f(50.f, -50.f, 50.f);

    glColor3f(1, 0, 0);
    glVertex3f(-50.f, 50.f, 50.f);
    glVertex3f(-50.f, 50.f, -50.f);
    glVertex3f(50.f, 50.f, -50.f);
    glVertex3f(50.f, 50.f, 50.f);

    glEnd();
  }

  MainMenuScene *MainMenuScene::Get() {
    static MainMenuScene instance;
    return &instance;
  }
}