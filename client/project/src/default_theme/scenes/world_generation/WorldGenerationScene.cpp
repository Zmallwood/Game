#include "WorldGenerationScene.h"
#include "../../../world_generation/WorldGenerator.h"
#include "core/scenes_core/SceneManager.h"

namespace Zmallwood {
  WorldGenerationScene::WorldGenerationScene() {
    {
      auto label = tgui::Label::create();
      label->setText("Generating world...");
      label->getRenderer()->setTextColor(tgui::Color::White);
      label->setPosition("(parent.width - width)/2", "50%");
      GUI()->add(label);
    }
  }

  void WorldGenerationScene::Update() {
    static bool hasSkippedUpdateFirstFrame = false;

    if (hasSkippedUpdateFirstFrame) {
      WorldGenerator::Get()->GenerateWorld();
      SceneManager::Get()->EnterScene("MainScene");
    }

    hasSkippedUpdateFirstFrame = true;
  }

  void WorldGenerationScene::Render3D() {}

  WorldGenerationScene *WorldGenerationScene::Get() {
    static WorldGenerationScene instance;
    return &instance;
  }
}