#include "CameraZooming.h"
#include "world_view/Camera.h"
#include "core/input/MouseInput.h"

namespace Zmallwood {
    void UpdateCameraZooming() {
        auto zoomSensitivity = 1.0f;
        auto cameraDistance = Camera::Get()->CameraDistance();
        cameraDistance += MouseInput::Get()->MouseWheelDeltaPickResult()*zoomSensitivity;
        Camera::Get()->SetCameraDistance(cameraDistance);
    }
}