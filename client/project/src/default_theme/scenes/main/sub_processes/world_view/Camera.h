#pragma once

namespace Zmallwood
{
  class Camera
  {
  public:
    void Update();
    void AddHorizontalAngleDelta(float delta);
    void AddVerticalAngleDelta(float delta);
    auto CameraDistance() const { return m_cameraDistance; }
    void SetCameraDistance(float value) { m_cameraDistance = value; }
    void SetUseFixedCameraDistance(bool value)
    {
      m_useFixedCameraDistance = value;
    }

    static Camera* Get();

  private:
    Camera() = default;
    void SetPerspectiveMatrix(void);
    void SetViewMatrix(void);
    Point3F GetCameraPosition(void);

    float m_cameraHeight = 8.0f;
    float m_usedFov = 110.0f;
    float m_cameraDistance = 1.0f;
    float m_horizontalAngleDegrees = 0.0f;
    float m_verticalAngleDegrees = -80.0f;
    bool m_useFixedCameraDistance = false;
    const float k_fixedCameraDistance = 500.0f;
  };
}