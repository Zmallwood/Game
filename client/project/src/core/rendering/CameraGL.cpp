#include "CameraGL.h"

namespace zw
{
  CameraGL*
  CameraGL::Get()
  {
    static CameraGL instance;                   // Create singleton instance once
    return &instance;
  }
}