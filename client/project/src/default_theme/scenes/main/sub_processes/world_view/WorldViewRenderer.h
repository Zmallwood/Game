#pragma once

namespace zw
{
  class WorldViewRenderer
  {
  public:
    void Initialize();
    void UpdateCamera();
    void RenderWorldView();
    static WorldViewRenderer* Get();

  private:
    WorldViewRenderer() = default;

    GLuint m_tileSurfaceID = -1;
    std::vector<std::vector<GLuint>> m_tileIDs;
  };
}