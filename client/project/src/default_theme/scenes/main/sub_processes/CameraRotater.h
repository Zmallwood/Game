#pragma once

namespace Zmallwood
{
  class CameraRotater
  {
  public:
    void Update();
    static CameraRotater* Get();

  private:
    PointF m_prevMousePosRotation;
    const float k_rotationSensHoriz = 100.0f;
    const float k_rotationSensVert = 100.0f;
  };
}