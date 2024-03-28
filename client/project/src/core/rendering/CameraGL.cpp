#include "CameraGL.h"

namespace Zmallwood
{
  CameraGL*
  CameraGL::Get()
  {
    static CameraGL instance;                   // Create singleton instance once
    return &instance;
  }
}