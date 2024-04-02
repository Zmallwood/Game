#include "CameraRotater.h"
#include "core/input/MouseInput.h"
#include "world_view/Camera.h"

namespace Zmallwood
{
  void CameraRotater::Update()
  {
    auto isRotating = MouseInput::Get()->RightButton().Pressed();

    auto mousePos = MousePosition();
    
    if (isRotating)
    {
      auto dx = mousePos.x - m_prevMousePosRotation.x;
      auto dy = mousePos.y - m_prevMousePosRotation.y;
      
      Camera::Get()->AddHorizontalAngleDelta(-dx * k_rotationSensHoriz);
      Camera::Get()->AddVerticalAngleDelta(-dy * k_rotationSensVert);
    }
    m_prevMousePosRotation.x = mousePos.x;
    m_prevMousePosRotation.y = mousePos.y;
  }

  CameraRotater* CameraRotater::Get()
  {
    static CameraRotater instance;
    return &instance;
  }
}