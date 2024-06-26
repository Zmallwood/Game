#include "TileRenderer.h"
#include "../../../world_structure/World.h"
#include "../../../world_structure/WorldArea.h"
#include "../../../world_structure/Tile.h"
#include "core/Player.h"
#include "core/assets/TextureBank.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/CameraGL.h"
#include "core/rendering/ShaderProgram.h"
#include "shaders/ShaderGroundFragment.h"
#include "shaders/ShaderGroundVertex.h"

namespace zw
{
  TileRenderer::TileRenderer()
    : RendererBase()
  {
    ShaderProgram()->Create(shaderGroundVertex, shaderGroundFragment);// Create shader program
    m_locProjection = GetUniformLocation("projection");               // Get projection loc. from shader
    m_locView = GetUniformLocation("view");                           // Get view loc. from shader
    m_locModel = GetUniformLocation("model");                         // Get model loc. from shader
    m_locViewPos = GetUniformLocation("viewPos");                     // Get view position loc. from shader
    m_locFogColor = GetUniformLocation("fogColor");                   // Get fog color loc. from shader
  }

  GLuint TileRenderer::NewTileSurface()
  {
    auto worldArea = World::Get()->WorldArea();
    auto numVerts = 6 * worldArea->Width() * worldArea->Height();     // 1 Rect=2 Triangles=2*3 vertices
    auto id = GenNewVAOID();                                          // Vertex array object (VAO) id
    auto indexBuffID = GenNewBuffID(BufferTypes::Indices, id);        // Indices vertex buffer object id
    auto posBuffID = GenNewBuffID(BufferTypes::Positions3D, id);      // Pos. vertex buffer object id
    auto colorBuffID = GenNewBuffID(BufferTypes::Colors, id);         // Colors vertex buffer object id
    auto uvBuffID = GenNewBuffID(BufferTypes::Uvs, id);               // UVs vertex buffer object id
    auto normBuffID = GenNewBuffID(BufferTypes::Normals, id);         // Normal vertex buffer object id
    glBindVertexArray(id);                                            // Use VAO
    SetIndicesData(indexBuffID, numVerts, nullptr);                   // Send empty indices data
    SetData(posBuffID, numVerts, nullptr, BufferTypes::Positions3D);  // Send empty positions data
    SetData(colorBuffID, numVerts, nullptr, BufferTypes::Colors);     // Send empty colors data
    SetData(uvBuffID, numVerts, nullptr, BufferTypes::Uvs);           // Send empty UVs data
    SetData(normBuffID, numVerts, nullptr, BufferTypes::Normals);     // Send empty normals data
    glBindVertexArray(0);                                             // Stop using VAO

    return id;
  }

  void TileRenderer::SetTileSurfaceGeom(GLuint VAOID, std::vector<std::vector<Square<Vertex3F>>>& vertices)
  {
    std::vector<Vertex3F> vertsTriangles;                             // To hold verts composing the tri's

    for (auto y = 0; y < vertices.size(); y++)
    {
      for (auto x = 0; x < vertices.at(0).size(); x++)
      {
        auto entry = vertices.at(x).at(y);
        vertsTriangles.push_back(entry._00);                          // Add north west corner
        vertsTriangles.push_back(entry._10);                          // Add north east corner
        vertsTriangles.push_back(entry._11);                          // Add south east corner
        vertsTriangles.push_back(entry._00);                          // Add north west corner again
        vertsTriangles.push_back(entry._11);                          // Add south east corner again
        vertsTriangles.push_back(entry._01);                          // Add south west corner
      }
    }

    UseVAOBegin(VAOID);                                             // Start using the VAO for tile surf.

    std::vector<int> indices(vertsTriangles.size());                  // To hold indices data
    std::iota(std::begin(indices), std::end(indices), 0);             // Fill indices with number sequence
    std::vector<float> positions;                                     // To hold positions
    std::vector<float> colors;                                        // To hold colors
    std::vector<float> uvs;                                           // To hold UVs
    std::vector<float> normals;                                       // To hold normals

    for (auto& vert : vertsTriangles)                                 // Iterate through triangle verts
    {
      positions.push_back(vert.position.x);                           // Copy position data to position vec
      positions.push_back(vert.position.y);
      positions.push_back(vert.position.z);
      colors.push_back(vert.color.r);                                 // Copy colors data to colors vec
      colors.push_back(vert.color.g);
      colors.push_back(vert.color.b);
      colors.push_back(vert.color.a);
      uvs.push_back(vert.uv.x);                                       // Copy UVs data to UVs vec
      uvs.push_back(vert.uv.y);
      normals.push_back(vert.normal.x);                               // Copy normal data to normals vec
      normals.push_back(vert.normal.y);
      normals.push_back(vert.normal.z);
    }

    {
      auto indexBuffID = GetBuffID(BufferTypes::Indices, VAOID);      // Get previously created index buff
      auto posBuffID = GetBuffID(BufferTypes::Positions3D, VAOID);    // Get previously created pos. buff
      auto colorBuffID = GetBuffID(BufferTypes::Colors, VAOID);       // Get previously created colors buff
      auto uvBuffID = GetBuffID(BufferTypes::Uvs, VAOID);             // Get previously created UVs buff
      auto normBuffID = GetBuffID(BufferTypes::Normals, VAOID);       // Get previously created normals buff
      glBindVertexArray(VAOID);

      // Send all the data vectors to each corresponding buffer
      UpdateIndicesData(indexBuffID, indices);
      UpdateData(posBuffID, positions, BufferTypes::Positions3D, k_locPosition);
      UpdateData(colorBuffID, colors, BufferTypes::Colors, k_locColor);
      UpdateData(uvBuffID, uvs, BufferTypes::Uvs, k_locUv);
      UpdateData(normBuffID, normals, BufferTypes::Normals, k_locNormal);
      glBindVertexArray(0);                                           // Stop using VAO
    }

    UseVAOEnd();                                                    // Stop using VAO
  }

  void TileRenderer::DrawTileSurface(const std::string& imageName, GLuint VAOID, bool depthTestOff)
  {
    auto worldArea = World::Get()->WorldArea();
    auto vertCount = 6 * worldArea->Width() * worldArea->Height();    // 1 Rect=2 Triangles=2*3 vertices

    // Depth test setting
    if (depthTestOff)
    {
      glDisable(GL_DEPTH_TEST);
    }
    else
    {
      glEnable(GL_DEPTH_TEST);
    }

    UseVAOBegin(VAOID);                                               // Start using VAO for tile surf.
    glUseProgram(ShaderProgram()->ProgramID());                       // Using shader program for ground
    // Set perspective matrix
    glUniformMatrix4fv(m_locProjection, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->PerspectiveMatrix()));
    // Set view matrx
    glUniformMatrix4fv(m_locView, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->ViewMatrix()));
    // Set model matrix
    glm::mat4 model(1.0);                                             // Create identity matrix
    glUniformMatrix4fv(m_locModel, 1, GL_FALSE, glm::value_ptr(model));

    // Set view position vector
    auto playerPos =                                                  // Get player pos. in GL space
      Player::Get()->Position().Multiply(GameProps::Get()->TileSize());
    auto tile = worldArea->GetTile(Player::Get()->Position().GetXZ().ToIntPoint());
    auto elev = tile->Elevation() * GameProps::Get()->ElevationScale();
    playerPos.y = elev;
    glm::vec3 viewPos(playerPos.x, playerPos.y, playerPos.z);
    glUniform3fv(m_locViewPos, 1, glm::value_ptr(viewPos));

    // Set fog color vector
    auto fogColorF = k_fogColorGround.ToColorF();                     // Convert to float type color values
    glm::vec3 fogColorGLM(fogColorF.r, fogColorF.g, fogColorF.b);     // Convert to glm vec type
    glUniform3fv(m_locFogColor, 1, glm::value_ptr(fogColorGLM));

    glUseProgram(ShaderProgram()->ProgramID());                       // Use shader program

    glEnable(GL_CULL_FACE);                                           // Use cull face to save FPS
    glCullFace(GL_BACK);                                              // Call tile back surf (underground)
    glFrontFace(GL_CW);                                               // Use clockwise vertices order

    TextureBank::Get()->BindTexture(imageName);                       // Bind texture with name

    glBindVertexArray(VAOID);                                         // Use tile surf. VAO
    glDrawElements(GL_TRIANGLES, vertCount, GL_UNSIGNED_INT, NULL);   // Do the drawing
    TextureBank::Get()->UnbindTexture();                              // Unbind used texture
    glBindVertexArray(0);                                             // Stop using VAO
    glUseProgram(0);                                                  // Stop using shader program
    glDisable(GL_CULL_FACE);                                          // Disable face culling
  }

  GLuint TileRenderer::NewTile()
  {
    auto numVerts = 4;
    auto RID = GenNewVAOID();
    auto indexBufID = GenNewBuffID(BufferTypes::Indices, RID);
    auto posBufID = GenNewBuffID(BufferTypes::Positions3D, RID);
    auto colorBufID = GenNewBuffID(BufferTypes::Colors, RID);
    auto uvBufID = GenNewBuffID(BufferTypes::Uvs, RID);
    auto normBufID = GenNewBuffID(BufferTypes::Normals, RID);
    glBindVertexArray(RID);
    SetIndicesData(indexBufID, numVerts, nullptr);
    SetData(posBufID, numVerts, nullptr, BufferTypes::Positions3D);
    SetData(colorBufID, numVerts, nullptr, BufferTypes::Colors);
    SetData(uvBufID, numVerts, nullptr, BufferTypes::Uvs);
    SetData(normBufID, numVerts, nullptr, BufferTypes::Normals);
    glBindVertexArray(0);

    return RID;
  }

  void TileRenderer::SetTileGeom(GLuint VAOID, Square<Vertex3F>& verts)
  {
    std::vector<Vertex3F> vertsVec;
    vertsVec.push_back(verts._00);
    vertsVec.push_back(verts._10);
    vertsVec.push_back(verts._11);
    vertsVec.push_back(verts._01);

    UseVAOBegin(VAOID);

    std::vector<int> indices(vertsVec.size());
    std::iota(std::begin(indices), std::end(indices), 0);
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> uvs;
    std::vector<float> normals;

    for (auto& vert : vertsVec)
    {
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

    auto indexBufID = GetBuffID(BufferTypes::Indices, VAOID);
    auto posBufID = GetBuffID(BufferTypes::Positions3D, VAOID);
    auto colorBufID = GetBuffID(BufferTypes::Colors, VAOID);
    auto uvBufID = GetBuffID(BufferTypes::Uvs, VAOID);
    auto normBufID = GetBuffID(BufferTypes::Normals, VAOID);
    glBindVertexArray(VAOID);
    UpdateIndicesData(indexBufID, indices);
    UpdateData(posBufID, positions, BufferTypes::Positions3D, k_locPosition);
    UpdateData(colorBufID, colors, BufferTypes::Colors, k_locColor);
    UpdateData(uvBufID, uvs, BufferTypes::Uvs, k_locUv);
    UpdateData(normBufID, normals, BufferTypes::Normals, k_locNormal);
    glBindVertexArray(0);

    UseVAOEnd();
  }

  void TileRenderer::DrawTile(const std::string& imgName, GLuint VAOID, bool depthTestOff)
  {
    auto vertCount = 4;

    if (depthTestOff)
      glDisable(GL_DEPTH_TEST);
    else
      glEnable(GL_DEPTH_TEST);

    UseVAOBegin(VAOID);
    glUniformMatrix4fv(m_locProjection, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->PerspectiveMatrix()));
    glUniformMatrix4fv(m_locView, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->ViewMatrix()));
    glm::mat4 model(1.0);
    glUniformMatrix4fv(m_locModel, 1, GL_FALSE, glm::value_ptr(model));
    auto playerPos = Player::Get()->Position().Multiply(GameProps::Get()->TileSize());
    auto worldArea = World::Get()->WorldArea();
    auto tile = worldArea->GetTile(Player::Get()->Position().GetXZ().ToIntPoint());
    auto elev = tile->Elevation() * GameProps::Get()->ElevationScale();
    playerPos.y = elev;
    glm::vec3 viewPos(playerPos.x, playerPos.y, playerPos.z);
    glUniform3fv(m_locViewPos, 1, glm::value_ptr(viewPos));
    auto fogColorF = k_fogColorGround.ToColorF();                     // Convert to float type color values
    glm::vec3 fogColorGLM(fogColorF.r, fogColorF.g, fogColorF.b);     // Convert to glm vec type
    glUniform3fv(m_locFogColor, 1, glm::value_ptr(fogColorGLM));

    TextureBank::Get()->BindTexture(imgName);
    glBindVertexArray(VAOID);
    glDrawElements(GL_TRIANGLE_FAN, vertCount, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    TextureBank::Get()->UnbindTexture();

    UseVAOEnd();
  }

  TileRenderer::~TileRenderer()
  {
    CleanupBase();                                                    // Cleanup all VAOs/VBOs in base
  }

  TileRenderer* TileRenderer::Get()
  {
    static TileRenderer instance;                              // Create singleton instance once
    return &instance;
  }
}