#pragma once

namespace Zmallwood
{
  /**
   * \brief Manages perspective and view matrix for the 3D world view
  */
  class CameraGL
  {
  public:
    // Getters/Setters
    auto PerspectiveMatrix() const { return m_perspectiveMatrix; }
    void SetPerspectiveMatrix(glm::mat4 value) { m_perspectiveMatrix = value; }
    auto ViewMatrix() const { return m_viewMatrix; }
    void SetViewMatrix(glm::mat4 value) { m_viewMatrix = value; }

    /**
     * \brief Get singleton instance
     * 
     * \return Singleton instance
    */
    static CameraGL* Get();

  private:
    /**
     * \brief Private constructor to force use singleton instance
    */
    CameraGL() = default;

    glm::mat4 m_perspectiveMatrix;              ///< Perspective matrix 
    glm::mat4 m_viewMatrix;                     ///< View matrix 
  };
}