#include "CameraZooming.h"
#include "core/input/MouseInput.h"
#include "world_view/Camera.h"

namespace Zmallwood
{
  void
  UpdateCameraZooming()
  {
    auto zoomSensitivity = 1.0f;
    auto cameraDistance = Camera::Get()->CameraDistance();
    cameraDistance +=
      MouseInput::Get()->MouseWheelDeltaPickResult() * zoomSensitivity;
    Camera::Get()->SetCameraDistance(cameraDistance);
  }
}