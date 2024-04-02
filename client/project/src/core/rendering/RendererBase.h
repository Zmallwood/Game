#pragma once
#include "BufferTypes.h"

namespace zw
{
  class ShaderProgram;

  class RendererBase
  {
  protected:
    RendererBase();
    GLuint GenNewVAOID();
    GLuint GenNewBuffID(BufferTypes buffType, GLuint VAOID);
    void SetIndicesData(GLuint indicesVBOID,
                        int numVertices,
                        const void* data) const;
    void SetData(GLuint VBOID,
                 int numVertices,
                 const void* data,
                 BufferTypes buffType,
                 int layoutLocation = -1) const;
    GLuint GetUniformLocation(const std::string& variableName);
    void UseVAOBegin(GLuint VAOID) const;
    GLuint GetBuffID(BufferTypes buffType, GLuint VAOID) const;
    void UpdateIndicesData(GLuint indicesVBOID,
                           std::vector<int>& indices) const;
    void UpdateData(GLuint VBOID,
                    std::vector<float>& data,
                    BufferTypes buffType,
                    int layoutLocation) const;
    void UseVAOEnd() const;
    void CleanupBase() const;
    auto ShaderProgram() { return m_shaderProgram; }

  private:
    void SetArrayBufferData(GLuint VBOID,
                            int numVertices,
                            const void* data,
                            int numFloatsPerEntry,
                            int layoutLocation = -1) const;
    void SetArrayBufferDataInt(GLuint VBOID,
                               int numVertices,
                               const void* data,
                               int numFloatsPerEntry,
                               int layoutLocation = -1) const;
    void UpdateArrayBufferData(GLuint VBOID,
                               std::vector<float>& data,
                               int numFloatsPerEntry,
                               int layoutLocation) const;
    void UpdateArrayBufferDataInt(GLuint VBOID,
                                  std::vector<float>& data,
                                  int numFloatsPerEntry,
                                  int layoutLocation) const;

    std::vector<GLuint> m_VAOIDs;
    std::map<BufferTypes, std::map<GLuint, GLuint>> m_VBOIDs;
    std::shared_ptr<zw::ShaderProgram> m_shaderProgram;
    inline static const auto k_numFloatsPerEntry = std::map<BufferTypes, int>{
      { BufferTypes::Indices, 1 },     { BufferTypes::Positions2D, 2 },
      { BufferTypes::Positions3D, 3 }, { BufferTypes::Colors, 4 },
      { BufferTypes::Uvs, 2 },         { BufferTypes::Normals, 3 },
      { BufferTypes::BoneIDs, 4 },     { BufferTypes::Weights, 4 }
    };
  };
}