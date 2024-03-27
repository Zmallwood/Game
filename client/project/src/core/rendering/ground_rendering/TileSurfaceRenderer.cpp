#include "TileSurfaceRenderer.h"
#include "core/rendering/ShaderProgram.h"
#include "shaders/ShaderGroundFragment.h"
#include "shaders/ShaderGroundVertex.h"
#include "core/rendering/CameraGL.h"
#include "core/Player.h"
#include "core/GameProps.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "core/assets/TextureBank.h"

namespace Zmallwood {
  TileSurfaceRenderer::TileSurfaceRenderer() : RendererBase() {
    ShaderProgram()->Create(shaderGroundVertex, shaderGroundFragment);
    m_locProjection = GetUniformLocation("projection");
    m_locView = GetUniformLocation("view");
    m_locModel = GetUniformLocation("model");
    m_locViewPos = GetUniformLocation("viewPos");
    m_locFogColor = GetUniformLocation("fogColor");
  }

  GLuint TileSurfaceRenderer::NewTileSurface() {
    auto numVerts = 6 * 100 * 100;
    auto id = GenNewVAOID();
    auto indexBuffID = GenNewBuffID(BufferTypes::Indices, id);
    auto posBuffID = GenNewBuffID(BufferTypes::Positions3D, id);
    auto colorBuffID = GenNewBuffID(BufferTypes::Colors, id);
    auto uvBuffID = GenNewBuffID(BufferTypes::Uvs, id);
    auto normBuffID = GenNewBuffID(BufferTypes::Normals, id);
    glBindVertexArray(id);
    SetIndicesData(indexBuffID, numVerts, nullptr);
    SetData(posBuffID, numVerts, nullptr, BufferTypes::Positions3D);
    SetData(colorBuffID, numVerts, nullptr, BufferTypes::Colors);
    SetData(uvBuffID, numVerts, nullptr, BufferTypes::Uvs);
    SetData(normBuffID, numVerts, nullptr, BufferTypes::Normals);
    glBindVertexArray(0);

    return id;
  }

  void TileSurfaceRenderer::SetTileSurfaceGeom(
      GLuint VAOID, std::vector<std::vector<Square<Vertex3F>>> &vertices) {
    std::vector<Vertex3F> vertsTriangles;

    for (auto y = 0; y < vertices.size(); y++) {
      for (auto x = 0; x < vertices.at(0).size(); x++) {
        auto entry = vertices.at(x).at(y);
        vertsTriangles.push_back(entry._00);
        vertsTriangles.push_back(entry._10);
        vertsTriangles.push_back(entry._11);
        vertsTriangles.push_back(entry._00);
        vertsTriangles.push_back(entry._11);
        vertsTriangles.push_back(entry._01);
      }
    }

    if (!m_isBatchDrawing) {
      UseVAOBegin(VAOID);
    }

    std::vector<int> indices(vertsTriangles.size());
    std::iota(std::begin(indices), std::end(indices), 0);
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> uvs;
    std::vector<float> normals;

    for (auto &vert : vertsTriangles) {
      positions.push_back(vert.position.x);
      positions.push_back(vert.position.y);
      positions.push_back(vert.position.z);
      colors.push_back(vert.color.r);
      colors.push_back(vert.color.g);
      colors.push_back(vert.color.b);
      colors.push_back(vert.color.a);
      uvs.push_back(vert.uv.x);
      uvs.push_back(vert.uv.y);
      auto vert_normal = vert.normal;
      normals.push_back(vert_normal.x);
      normals.push_back(vert_normal.y);
      normals.push_back(vert_normal.z);
    }

    {
      auto indexBuffID = GetBuffID(BufferTypes::Indices, VAOID);
      auto posBuffID = GetBuffID(BufferTypes::Positions3D, VAOID);
      auto colorBuffID = GetBuffID(BufferTypes::Colors, VAOID);
      auto uvBuffID = GetBuffID(BufferTypes::Uvs, VAOID);
      auto normBuffID = GetBuffID(BufferTypes::Normals, VAOID);
      glBindVertexArray(VAOID);

      UpdateIndicesData(indexBuffID, indices);
      UpdateData(posBuffID, positions, BufferTypes::Positions3D, k_locPosition);
      UpdateData(colorBuffID, colors, BufferTypes::Colors, k_locColor);
      UpdateData(uvBuffID, uvs, BufferTypes::Uvs, k_locUv);
      UpdateData(normBuffID, normals, BufferTypes::Normals, k_locNormal);
      glBindVertexArray(0);
    }

    if (!m_isBatchDrawing) {
      UseVAOEnd();
    }
  }

  void TileSurfaceRenderer::DrawTileSurface(const std::string &imageName,
                                            GLuint VAOID, bool depthTestOff) {
    auto worldArea = World::Get()->WorldArea();
    auto vertCount = 6 * worldArea->Width() * worldArea->Height();

    if (depthTestOff) {
      glDisable(GL_DEPTH_TEST);
    } else {
      glEnable(GL_DEPTH_TEST);
    }

    UseVAOBegin(VAOID);
    glUseProgram(ShaderProgram()->ProgramID());
    glUniformMatrix4fv(m_locProjection, 1, GL_FALSE,
                       glm::value_ptr(CameraGL::Get()->PerspectiveMatrix()));
    glUniformMatrix4fv(m_locView, 1, GL_FALSE,
                       glm::value_ptr(CameraGL::Get()->ViewMatrix()));
    glm::mat4 model(1.0);
    glUniformMatrix4fv(m_locModel, 1, GL_FALSE, glm::value_ptr(model));

    auto playerPos = Player::Get()->Position().Multiply(
        GameProps::Get()->TileSize());

    glm::vec3 viewPos(playerPos.x, playerPos.y, playerPos.z);
    glUniform3fv(m_locViewPos, 1, glm::value_ptr(viewPos));
    auto fogColorF = k_fogColorGround.ToColorF();
    glm::vec3 fogColorGLM(fogColorF.r, fogColorF.g, fogColorF.b);
    glUniform3fv(m_locFogColor, 1, glm::value_ptr(fogColorGLM));
    glUseProgram(ShaderProgram()->ProgramID());
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    TextureBank::Get()->BindTexture(imageName);
    glBindVertexArray(VAOID);
    glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, NULL);
    TextureBank::Get()->UnbindTexture();
    glBindVertexArray(0);
    glUseProgram(0);
    glDisable(GL_CULL_FACE);
  }

  TileSurfaceRenderer::~TileSurfaceRenderer() {
    CleanupBase();
  }

  TileSurfaceRenderer *TileSurfaceRenderer::Get() {
    static TileSurfaceRenderer instance;
    return &instance;
  }
}