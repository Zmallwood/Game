#include "RendererBase.h"
#include "ShaderProgram.h"

namespace Zmallwood
{
  RendererBase::RendererBase()
    : m_shaderProgram(std::make_shared<Zmallwood::ShaderProgram>())
  {
  }

  GLuint
  RendererBase::GenNewVAOID()
  {
    GLuint VAOID;
    glGenVertexArrays(1, &VAOID);
    m_VAOIDs.push_back(VAOID);

    return VAOID;
  }

  GLuint
  RendererBase::GenNewBuffID(BufferTypes buffType, GLuint VAOID)
  {
    GLuint buffID;
    glGenBuffers(1, &buffID);
    m_VBOIDs[buffType][VAOID] = buffID;

    return buffID;
  }

  void
  RendererBase::SetIndicesData(GLuint indicesVBOID,
                               int numVertices,
                               const void* data) const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 numVertices * k_numFloatsPerEntry.at(BufferTypes::Indices) *
                   sizeof(float),
                 data,
                 GL_DYNAMIC_DRAW);
  }

  void
  RendererBase::SetData(GLuint VBOID,
                        int numVertices,
                        const void* data,
                        BufferTypes buffType,
                        int layoutLocation) const
  {
    if (buffType == BufferTypes::BoneIDs)
    {
      SetArrayBufferDataInt(VBOID,
                            numVertices,
                            data,
                            RendererBase::k_numFloatsPerEntry.at(buffType),
                            layoutLocation);
    }
    else
    {
      SetArrayBufferData(VBOID,
                         numVertices,
                         data,
                         RendererBase::k_numFloatsPerEntry.at(buffType),
                         layoutLocation);
    }
  }

  void
  RendererBase::SetArrayBufferData(GLuint VBOID,
                                   int numVertices,
                                   const void* data,
                                   int numFloatsPerEntry,
                                   int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER,
                 numVertices * numFloatsPerEntry * sizeof(float),
                 data,
                 GL_DYNAMIC_DRAW);

    if (layoutLocation >= 0)
    {
      glVertexAttribPointer(layoutLocation,
                            numFloatsPerEntry,
                            GL_FLOAT,
                            GL_FALSE,
                            0,
                            (const GLvoid*)0);
      glEnableVertexAttribArray(layoutLocation);
    }
  }

  void
  RendererBase::SetArrayBufferDataInt(GLuint VBOID,
                                      int numVertices,
                                      const void* data,
                                      int numFloatsPerEntry,
                                      int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferData(GL_ARRAY_BUFFER,
                 numVertices * numFloatsPerEntry * sizeof(int),
                 data,
                 GL_DYNAMIC_DRAW);

    if (layoutLocation >= 0)
    {
      glEnableVertexAttribArray(3);
      glVertexAttribIPointer(
        layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid*)0);
      glEnableVertexAttribArray(layoutLocation);
    }
  }

  GLuint
  RendererBase::GetUniformLocation(const std::string& variableName)
  {
    return glGetUniformLocation(m_shaderProgram->ProgramID(),
                                variableName.c_str());
  }

  void
  RendererBase::UseVAOBegin(GLuint VAOID) const
  {
    glUseProgram(m_shaderProgram->ProgramID());
    glBindVertexArray(VAOID);
  }

  GLuint
  RendererBase::GetBuffID(BufferTypes buffType, GLuint VAOID) const
  {
    return m_VBOIDs.at(buffType).at(VAOID);
  }

  void
  RendererBase::UpdateIndicesData(GLuint indicesVBOID,
                                  std::vector<int>& indices) const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBOID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                    0,
                    sizeof(float) * indices.size(),
                    indices.data());
  }

  void
  RendererBase::UpdateArrayBufferData(GLuint VBOID,
                                      std::vector<float>& data,
                                      int numFloatsPerEntry,
                                      int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferSubData(
      GL_ARRAY_BUFFER, 0, sizeof(float) * data.size(), data.data());
    glVertexAttribPointer(layoutLocation,
                          numFloatsPerEntry,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (const GLvoid*)0);
    glEnableVertexAttribArray(layoutLocation);
  }

  void
  RendererBase::UpdateArrayBufferDataInt(GLuint VBOID,
                                         std::vector<float>& data,
                                         int numFloatsPerEntry,
                                         int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(int) * data.size(), data.data());
    glVertexAttribIPointer(
      layoutLocation, numFloatsPerEntry, GL_INT, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(layoutLocation);
  }

  void
  RendererBase::UpdateData(GLuint VBOID,
                           std::vector<float>& data,
                           BufferTypes buffType,
                           int layoutLocation) const
  {
    if (buffType == BufferTypes::BoneIDs)
    {
      UpdateArrayBufferDataInt(VBOID,
                               data,
                               RendererBase::k_numFloatsPerEntry.at(buffType),
                               layoutLocation);
    }
    else
    {
      UpdateArrayBufferData(VBOID,
                            data,
                            RendererBase::k_numFloatsPerEntry.at(buffType),
                            layoutLocation);
    }
  }

  void
  RendererBase::UseVAOEnd() const
  {
    glBindVertexArray(0);
    glUseProgram(0);
  }

  void
  RendererBase::CleanupBase() const
  {
    for (auto& bufType : m_VBOIDs)
    {
      for (auto& bufferEntry : bufType.second)
      {
        glDeleteBuffers(1, &bufferEntry.second);
      }
    }

    for (auto VAOID : m_VAOIDs)
    {
      glDeleteVertexArrays(1, &VAOID);
    }

    m_shaderProgram->Cleanup();
  }
}