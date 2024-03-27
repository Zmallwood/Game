#pragma once
#include "IScene.h"

namespace Zmallwood
{
  class SceneManager
  {
  public:
    void HandleEventCurrentScene(sf::Event event);
    void UpdateCurrentScene();
    void RenderCurrentScene();
    void EnterScene(const std::string& scene);
    static SceneManager* Get();

  private:
    SceneManager();

    std::map<int, IScene*> m_scenes;
    int m_currentScene = 0;
  };
}