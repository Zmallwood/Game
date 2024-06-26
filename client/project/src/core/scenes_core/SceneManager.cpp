#include "SceneManager.h"
#include "default_theme/scenes/intro/IntroScene.h"
#include "default_theme/scenes/main/MainScene.h"
#include "default_theme/scenes/main_menu/MainMenuScene.h"
#include "default_theme/scenes/new_game/NewGameScene.h"
#include "default_theme/scenes/world_generation/WorldGenerationScene.h"

namespace zw
{
  SceneManager::SceneManager()
  {
    m_scenes.insert({ Hash("IntroScene"), IntroScene::Get() });
    m_scenes.insert({ Hash("MainMenuScene"), MainMenuScene::Get() });
    m_scenes.insert({ Hash("NewGameScene"), NewGameScene::Get() });
    m_scenes.insert({ Hash("WorldGenerationScene"), WorldGenerationScene::Get() });
    m_scenes.insert({ Hash("MainScene"), MainScene::Get() });

    EnterScene("IntroScene");
  }

  void SceneManager::HandleEventCurrentScene(sf::Event event)
  {
    if (m_scenes.contains(m_currentScene))
    {
      m_scenes.at(m_currentScene)->GUI()->handleEvent(event);
    }
  }

  void SceneManager::UpdateCurrentScene()
  {
    if (m_scenes.contains(m_currentScene))
    {
      m_scenes.at(m_currentScene)->Update();
    }
  }

  void SceneManager::RenderCurrentScene()
  {
    if (m_scenes.contains(m_currentScene))
    {
      m_scenes.at(m_currentScene)->Render();
    }
  }

  void SceneManager::RenderGUICurrentScene()
  {
    if (m_scenes.contains(m_currentScene))
    {
      m_scenes.at(m_currentScene)->RenderGUI();
    }
  }

  void SceneManager::EnterScene(const std::string& scene)
  {
    m_currentScene = Hash(scene);
    if (m_scenes.contains(m_currentScene))
    {
      m_scenes.at(m_currentScene)->OnEnter();
    }
  }

  SceneManager* SceneManager::Get()
  {
    static SceneManager instance;
    return &instance;
  }
}