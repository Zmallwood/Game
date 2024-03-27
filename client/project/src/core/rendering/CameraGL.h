#pragma once

namespace Zmallwood {
  class CameraGL {
   public:
    auto PerspectiveMatrix() const { return m_perspectiveMatrix; }
    void SetPerspectiveMatrix(glm::mat4 value) { m_perspectiveMatrix = value; }
    auto ViewMatrix() const { return m_viewMatrix; }
    void SetViewMatrix(glm::mat4 value) { m_viewMatrix = value; }
    static CameraGL *Get();

   private:
    CameraGL() = default;
    glm::mat4 m_perspectiveMatrix;
    glm::mat4 m_viewMatrix;
  };
}