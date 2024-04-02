#include "Engine.h"
#include "Graphics.h"
#include "PollEvents.h"
#include "core/Graphics.h"
#include "core/rendering/models_rendering/ModelRenderer.h"
#include "scenes_core/SceneManager.h"
#include "core/assets/AnimationBank.h"
#include "Cursor.h"

namespace zw
{
  Engine::Engine()
  {
    Graphics::Get();
    ModelRenderer::Get()->PrepareAllModels();
    Cursor::Get()->Initialize();
  }

  void
  Engine::HandleInput()
  {
    PollEvents();
  }

  void
  Engine::Update()
  {
    AnimationBank::Get()->UpdateAllAnimations();
    SceneManager::Get()->UpdateCurrentScene();
  }

  void
  Engine::Render()
  {
    SceneManager::Get()->RenderCurrentScene();
    Cursor::Get()->Render();
    Graphics::Get()->PresentCanvas();
  }

  Engine*
  Engine::Get()
  {
    static Engine instance;
    return &instance;
  }
}