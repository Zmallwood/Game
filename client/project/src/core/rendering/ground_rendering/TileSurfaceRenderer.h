#pragma once
#include "core/rendering/RendererBase.h"

namespace Zmallwood
{
  class TileSurfaceRenderer : public RendererBase
  {
  public:
    ~TileSurfaceRenderer();
    GLuint NewTileSurface();
    void SetTileSurfaceGeom(GLuint VAOID,
                            std::vector<std::vector<Square<Vertex3F>>>& verts);
    void DrawTileSurface(const std::string& imageName,
                         GLuint VAOID,
                         bool depthTestOff = false);
    static TileSurfaceRenderer* Get();

    static constexpr int k_locPosition = 0;
    static constexpr int k_locColor = 1;
    static constexpr int k_locUv = 2;
    static constexpr int k_locNormal = 3;
    Color k_fogColorGround = { .r = 0, .g = 150, .b = 255 };

  private:
    TileSurfaceRenderer();

    int m_locProjection = -1;
    int m_locView = -1;
    int m_locModel = -1;
    int m_locViewPos = -1;
    int m_locFogColor = -1;
    bool m_isBatchDrawing = false;
  };
}