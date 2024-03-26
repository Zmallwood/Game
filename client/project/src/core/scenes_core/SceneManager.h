#pragma once
#include "IScene.h"

namespace JoD {
    class SceneManager {
       public:
        void HandleEventCurrentScene(sf::Event event);
        void UpdateCurrentScene();
        void RenderCurrentScene();
        void EnterScene(int scene);
        static SceneManager *Get();

       private:
        SceneManager();

        std::map<int, IScene *> m_scenes;
        int m_currentScene = 0;
    };
}