#include "Engine.h"
#include "PollEvents.h"
#include "Graphics.h"
#include "scenes_core/SceneManager.h"

namespace Zmallwood {
  void Engine::HandleInput() {
    PollEvents();
  }

  void Engine::Update() {
    SceneManager::Get()->UpdateCurrentScene();
  }

  void Engine::Render() {
    SceneManager::Get()->RenderCurrentScene();
  }

  Engine *Engine::Get() {
    static Engine instance;
    return &instance;
  }
}