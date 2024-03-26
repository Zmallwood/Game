#include "SceneManager.h"
#include "default_theme/scenes/game_over/GameOverScene.h"
#include "default_theme/scenes/intro/IntroScene.h"
#include "default_theme/scenes/main/MainScene.h"
#include "default_theme/scenes/main_menu/MainMenuScene.h"

namespace JoD {
    SceneManager::SceneManager() {
        m_scenes.insert({Hash("IntroScene"), IntroScene::Get()});
        m_scenes.insert({Hash("MainMenuScene"), MainMenuScene::Get()});
        m_scenes.insert({Hash("MainScene"), MainScene::Get()});
        m_scenes.insert({Hash("GameOverScene"), GameOverScene::Get()});

        EnterScene(Hash("IntroScene"));
    }

    void SceneManager::HandleEventCurrentScene(sf::Event event) {
        if (m_scenes.contains(m_currentScene)) {
            m_scenes.at(m_currentScene)->GUI()->handleEvent(event);
        }
    }

    void SceneManager::UpdateCurrentScene() {
        if (m_scenes.contains(m_currentScene)) {
            m_scenes.at(m_currentScene)->Update();
        }
    }

    void SceneManager::RenderCurrentScene() {
        if (m_scenes.contains(m_currentScene)) {
            m_scenes.at(m_currentScene)->Render();
        }
    }

    void SceneManager::EnterScene(int scene) {
        m_currentScene = scene;
        if (m_scenes.contains(m_currentScene)) {
            m_scenes.at(m_currentScene)->OnEnter();
        }
    }

    SceneManager *SceneManager::Get() {
        static SceneManager instance;
        return &instance;
    }
}