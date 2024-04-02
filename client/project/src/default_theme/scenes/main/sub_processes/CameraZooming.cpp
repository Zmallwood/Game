#include "CameraZooming.h"
#include "core/input/MouseInput.h"
#include "world_view/Camera.h"

namespace zw
{
  void
  UpdateCameraZooming()
  {
    auto zoomSensitivity = 0.05f;
    auto cameraDistance = Camera::Get()->CameraDistance();
    cameraDistance += MouseInput::Get()->MouseWheelDeltaPickResult() * zoomSensitivity;
    Camera::Get()->SetCameraDistance(cameraDistance);
  }
}