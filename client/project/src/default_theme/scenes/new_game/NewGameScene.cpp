#include "NewGameScene.h"
#include "core/scenes_core/SceneManager.h"

namespace Funtasia {
    NewGameScene::NewGameScene() {
        {
            auto label = tgui::Label::create();
            label->setText("Map width:");
            label->getRenderer()->setTextColor(tgui::Color::White);
            label->setPosition("(parent.width - width)/2","30%");
            GUI()->add(label);
        }
        {
            auto editBox = tgui::EditBox::create();
            editBox->setText("100");
            editBox->setPosition("(parent.width - width)/2","33%");
            GUI()->add(editBox, "EditBoxMapWidth");
        }
        {
            auto label = tgui::Label::create();
            label->setText("Map height:");
            label->getRenderer()->setTextColor(tgui::Color::White);
            label->setPosition("(parent.width - width)/2","40%");
            GUI()->add(label);
        }
        {
            auto editBox = tgui::EditBox::create();
            editBox->setText("100");
            editBox->setPosition("(parent.width - width)/2","43%");
            GUI()->add(editBox, "EditBoxMapHeight");
        }
        {
            auto button = tgui::Button::create("Start game");
            button->setSize({140, 40});
            button->setPosition("(parent.width - width)/2", "50%");
            button->onPress([] { SceneManager::Get()->EnterScene("WorldGenerationScene"); });
            GUI()->add(button);
        }
    }

    void NewGameScene::Update() {}

    void NewGameScene::Render3D() {
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

    NewGameScene *NewGameScene::Get() {
        static NewGameScene instance;
        return &instance;
    }
}