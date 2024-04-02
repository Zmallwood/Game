#pragma once
#include "core/rendering/RendererBase.h"

namespace zw
{
  class ModelRenderer : public RendererBase
  {
  public:
    ~ModelRenderer();
    void PrepareAllModels();
    void DrawModel(int modelNameHash,
                   int animNameHash,
                   float msTime,
                   Point3F position,
                   float rotation = 0.0f,
                   float scaling = 1.0f);
    static ModelRenderer* Get();

  private:
    ModelRenderer();
    void CreateModelResources(GLuint VAOID,
                              std::vector<GLMVertex> vertices,
                              std::vector<Point3F> vertexNormals);

    static constexpr int k_locPosition = 0;
    static constexpr int k_locNormal = 1;
    static constexpr int k_locUV = 2;
    static constexpr int k_locbBoneIds = 3;
    static constexpr int k_locWeights = 4;
    int m_locProjection = -1;
    int m_locView = -1;
    int m_locModel = -1;
    int m_locViewPos = -1;
    int m_locFogColor = -1;
    Color m_fogColorModels = Color{ .r = 0, .g = 150, .b = 255 };
    bool m_isBatchDrawing = false;
  };
}