#include "CameraGL.h"

namespace Zmallwood {
  CameraGL *CameraGL::Get() {
    static CameraGL instance;
    return &instance;
  }
}