#pragma once

namespace Zmallwood
{
  class IScene
  {
  public:
    IScene();
    ~IScene();
    virtual void OnEnter() {}
    virtual void Update() = 0;
    void Render();
    auto GUI() { return m_gui; }

  protected:
    virtual void Render3D() = 0;

  private:
    std::shared_ptr<tgui::Gui> m_gui;
    inline static GLuint m_FBO;
    inline static GLuint m_RBO;
    inline static GLuint m_texID;
    inline static GLuint m_VAO;
    inline static sf::Shader m_shader;
    inline static GLuint m_indexBufID;
    inline static GLuint m_posBufID;
    inline static GLuint m_colorBufID;
    inline static GLuint m_uvBufID;
  };
}