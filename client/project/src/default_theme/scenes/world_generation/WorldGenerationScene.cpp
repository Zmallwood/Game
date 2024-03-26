#include "WorldGenerationScene.h"
#include "../../../world_generation/WorldGenerator.h"

namespace Funtasia {
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
        WorldGenerator::Get()->GenerateWorld();
    }

    void WorldGenerationScene::Render3D() {}

    WorldGenerationScene *WorldGenerationScene::Get() {
        static WorldGenerationScene instance;
        return &instance;
    }
}