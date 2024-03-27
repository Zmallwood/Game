#include "FPSMeasuring.h"
#include "default_theme/scenes/main/MainScene.h"

namespace Zmallwood {
  void UpdateFPSMeasuring() {
    static int fps = 0;
    static int framesCount = 0;
    static int ticksLastUpdate = 0;

    if (Ticks() > ticksLastUpdate + 1000) {
      fps = framesCount;
      framesCount = 0;
      ticksLastUpdate = Ticks();
    }
    framesCount++;

    MainScene::Get()->GUI()->get<tgui::Label>("lblFPS")->setText(
        "FPS: " + std::to_string(fps));
  }
}