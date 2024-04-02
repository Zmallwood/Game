#include "IntroScene.h"
#include "core/input/KeyboardInput.h"
#include "core/input/MouseInput.h"
#include "core/scenes_core/SceneManager.h"

namespace zw
{
  IntroScene::IntroScene()
  {
    {
      m_startText = tgui::RichTextLabel::create("<color=white>Press to start</color>");
      m_startText->setPosition("(parent.width - width)/2", "(parent.height - height)/2");
      m_startText->setTextSize(20);
      GUI()->add(m_startText);
    }
  }

  void
  IntroScene::Update()
  {
    if (KeyboardInput::Get()->AnyKeyIsPressed() || MouseInput::Get()->AnyButtonPressed())
    {
      SceneManager::Get()->EnterScene("MainMenuScene");
    }
    if (Ticks() % 600 < 300)
    {
      m_startText->setVisible(false);
    }
    else
    {
      m_startText->setVisible(true);
    }
  }

  void
  IntroScene::Render3D()
  {
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

  IntroScene*
  IntroScene::Get()
  {
    static IntroScene instance;
    return &instance;
  }
}