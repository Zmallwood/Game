#include "ModelRenderer.h"
#include "core/Player.h"
#include "core/assets/AnimationBank.h"
#include "core/assets/ModelBank.h"
#include "core/assets/TextureBank.h"
#include "core/assets/animation_structure/Animator.h"
#include "core/assets/model_structure/Model.h"
#include "core/configuration/GameProps.h"
#include "core/rendering/CameraGL.h"
#include "core/rendering/ShaderProgram.h"
#include "shaders/ShaderModelsFragment.h"
#include "shaders/ShaderModelsVertex.h"

namespace Zmallwood
{
  ModelRenderer::ModelRenderer()
    : RendererBase()
  {
    std::cout << "create model rend\n";
    ShaderProgram()->Create(shaderModelsVertex, shaderModelsFragment);// Create shader program
    m_locProjection = GetUniformLocation("projection");
    m_locView = GetUniformLocation("view");
    m_locModel = GetUniformLocation("model");
    m_locViewPos = GetUniformLocation("viewPos");
    m_locFogColor = GetUniformLocation("fogColor");
  }

  void
  ModelRenderer::PrepareAllModels()
  {
    auto& models = ModelBank::Get()->Models();

    for (auto& entry : models)
    {
      auto model = entry.second;

      for (auto& mesh : model->meshes)
      {
        mesh.VAO = GenNewVAOID();
        CreateModelResources(mesh.VAO, mesh.vertices, {});
      }
    }
  }

  void
  ModelRenderer::CreateModelResources(GLuint VAOID,
                                      std::vector<GLMVertex> vertices,
                                      std::vector<Point3F> vertexNormals)
  {
    glEnable(GL_DEPTH_TEST);
    UseVAOBegin(VAOID);
    glUniformMatrix4fv(m_locProjection, 1, GL_FALSE, value_ptr(CameraGL::Get()->PerspectiveMatrix()));
    glUniformMatrix4fv(m_locView, 1, GL_FALSE, value_ptr(CameraGL::Get()->ViewMatrix()));
    std::vector<int> indices(vertices.size());
    std::iota(std::begin(indices), std::end(indices), 0);
    auto indexBufID = GenNewBuffID(BufferTypes::Indices, VAOID);
    auto positionBufID = GenNewBuffID(BufferTypes::Positions3D, VAOID);
    auto uvBufID = GenNewBuffID(BufferTypes::Uvs, VAOID);
    auto normalBufID = GenNewBuffID(BufferTypes::Normals, VAOID);
    auto boneIDsBufID = GenNewBuffID(BufferTypes::BoneIDs, VAOID);
    auto weightsBufID = GenNewBuffID(BufferTypes::Weights, VAOID);
    auto numVertices = vertices.size();
    auto VBO = GenNewBuffID(BufferTypes::Misc, VAOID);
    auto EBO = GenNewBuffID(BufferTypes::Misc, VAOID);
    glBindVertexArray(VAOID);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a
    // glm::vec3/2 array which again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLMVertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLMVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLMVertex), (void*)offsetof(GLMVertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLMVertex), (void*)offsetof(GLMVertex, texCoords));
    // vertex tangent
    // ids
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(GLMVertex), (void*)offsetof(GLMVertex, m_boneIDs));
    // weights
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(GLMVertex), (void*)offsetof(GLMVertex, m_weights));
    UseVAOEnd();
  }

  void
  ModelRenderer::DrawModel(int modelNameHash,
                           int animNameHash,
                           float msTime,
                           Point3F position,
                           float rotation,
                           float scaling)
  {
    // if (m_skelModelIDs->count(skelModelname.data()) == 0)
    //     return;
    if (!m_isBatchDrawing)
    {
      glEnable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glFrontFace(GL_CCW);
      glUseProgram(ShaderProgram()->ProgramID());
      glUniformMatrix4fv(m_locProjection, 1, GL_FALSE, value_ptr(CameraGL::Get()->PerspectiveMatrix()));
      glUniformMatrix4fv(m_locView, 1, GL_FALSE, glm::value_ptr(CameraGL::Get()->ViewMatrix()));
      auto playerPos = Player::Get()->Position().Multiply(GameProps::Get()->TileSize());

      auto tileSize = GameProps::Get()->TileSize();
      glm::vec3 viewPos(
        playerPos.x, playerPos.y /*+ CalcPlayerElevation(_<GameParameters>()->player)*/, playerPos.z);
      glUniform3fv(m_locViewPos, 1, glm::value_ptr(viewPos));
      auto fogColorF = m_fogColorModels.ToColorF();
      glm::vec3 fogColorGL(fogColorF.r, fogColorF.g, fogColorF.b);
      glUniform3fv(m_locFogColor, 1, glm::value_ptr(fogColorGL));
    }

    // auto anim = _<nSkelAnimBank>()->GetSkelAnim(skelAnimName);
    // auto transforms = _<AnimationBank>()->animator->FinalBoneMatrices();

    if (AnimationBank::Get()->GetAnimator(animNameHash, modelNameHash) != nullptr)
    {
      auto transforms = AnimationBank::Get()->GetAnimator(animNameHash, modelNameHash)->FinalBoneMatrices();

      for (int i = 0; i < transforms.size(); ++i)
      {
        auto str = "finalBonesMatrices[" + std::to_string(i) + "]";
        auto locFinalBonesMatrices = glGetUniformLocation(ShaderProgram()->ProgramID(), str.c_str());
        glUniformMatrix4fv(locFinalBonesMatrices, 1, GL_FALSE, glm::value_ptr(transforms[i]));
                //auto mat =
                //glm::rotate(glm::mat4(1.0),
                //            glm::radians(-90.0f), glm::vec3(1, 0, 0));

                //glUniformMatrix4fv(locFinalBonesMatrices, 1, GL_FALSE, glm::value_ptr(mat));
            //    ourShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
      }
    }
    else
    {
      for (int i = 0; i < 1; i++)
      {
        auto str = "finalBonesMatrices[" + std::to_string(i) + "]";
        auto locFinalBonesMatrices =
          glGetUniformLocation(ShaderProgram()->ProgramID(), str.c_str());
            //glUniformMatrix4fv(locFinalBonesMatrices, 1, GL_FALSE, glm::value_ptr(transforms[i]));
        auto mat = glm::rotate(glm::mat4(1.0), glm::radians(-90.0f), glm::vec3(1, 0, 0));

        glUniformMatrix4fv(locFinalBonesMatrices, 1, GL_FALSE, glm::value_ptr(mat));
            //    ourShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
      }
    }

    auto model = ModelBank::Get()->GetModel(modelNameHash);

    for (auto& mesh : model->meshes)
    {
      auto modelMatrix =
        glm::rotate(glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)),
                               glm::vec3(scaling * 0.5f, scaling * 0.5f, scaling * 0.5f)),
                    glm::radians(rotation + 90.0f),
                    glm::vec3(0, 1, 0));
      glUniformMatrix4fv(m_locModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
      glBindVertexArray(mesh.VAO);
      auto imgName = FilenameNoExtension(mesh.textures[0].path);
      TextureBank::Get()->BindTexture(imgName);
      glDrawElements(GL_TRIANGLES, mesh.vertices.size(), GL_UNSIGNED_INT, NULL);
      TextureBank::Get()->UnbindTexture();
    }

    glBindVertexArray(0);

    if (!m_isBatchDrawing)
      glUseProgram(0);
  }

  ModelRenderer::~ModelRenderer()
  {
    CleanupBase();
  }

  ModelRenderer*
  ModelRenderer::Get()
  {
    static ModelRenderer instance;
    return &instance;
  }
}