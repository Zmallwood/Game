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
    m_VAOIDs.push_back(VAOID);                  // Store newly created VAO id

    return VAOID;
  }

  GLuint
  RendererBase::GenNewBuffID(BufferTypes buffType, GLuint VAOID)
  {
    GLuint buffID;
    glGenBuffers(1, &buffID);
    m_VBOIDs[buffType][VAOID] = buffID;         // Store newly created VBO id,
                                                // with the VAO id as one of keys
    return buffID;
  }

  void
  RendererBase::SetIndicesData(GLuint indicesVBOID, int numVertices, const void* data) const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,       // Bind the VBO buffer that should hold indices data
                 indicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,       // Set indices data as element array buffer
                 numVertices * k_numFloatsPerEntry.at(BufferTypes::Indices) * sizeof(float),
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
      SetArrayBufferDataInt(VBOID,              // Call other method for BoneIDs than other buffer types
                            numVertices,
                            data,
                            RendererBase::k_numFloatsPerEntry.at(buffType),
                            layoutLocation);
    }
    else
    {
      SetArrayBufferData(VBOID,                 // Call this function for all buffer types except BoneIDs
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
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);       // Bind the VBO for the provided VBO id
    glBufferData(GL_ARRAY_BUFFER,               // Set the buffer data as an array buffer
                 numVertices * numFloatsPerEntry * sizeof(float),
                 data,
                 GL_DYNAMIC_DRAW);

    if (layoutLocation >= 0)                    // Is valid layout location?
    {
      glVertexAttribPointer(                    // Configure layout float float values
        layoutLocation,
        numFloatsPerEntry,
        GL_FLOAT,
        GL_FALSE,
        0,
        (const GLvoid*)0);
      glEnableVertexAttribArray(                // Enable layout
        layoutLocation);
    }
  }

  void 
  RendererBase::SetArrayBufferDataInt(GLuint VBOID,
                                      int numVertices,
                                      const void* data,
                                      int numFloatsPerEntry,
                                      int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);       // Bind the VBO for the provided VBO id
    glBufferData(GL_ARRAY_BUFFER,               // Set the buffer data as an array buffer
                 numVertices * numFloatsPerEntry * sizeof(int),
                 data,
                 GL_DYNAMIC_DRAW);

    if (layoutLocation >= 0)                    // Is valid layout location?
    {
      glEnableVertexAttribArray(3);             // Enable generic vertex attribute
      glVertexAttribIPointer(                   // Configure layout for int values
        layoutLocation,
        numFloatsPerEntry,
        GL_INT,
        0,
        (const GLvoid*)0);
      glEnableVertexAttribArray(                // Enable layout
        layoutLocation);
    }
  }

  GLuint
  RendererBase::GetUniformLocation(const std::string& variableName)
  {
    return glGetUniformLocation(                // Get layout location of uniform variable in the shader
      m_shaderProgram->ProgramID(),
      variableName.c_str());
  }

  void
  RendererBase::UseVAOBegin(GLuint VAOID) const
  {
    glUseProgram(m_shaderProgram->ProgramID()); // Start using shader  program and provided VAO
    glBindVertexArray(VAOID);
  }

  GLuint
  RendererBase::GetBuffID(BufferTypes buffType, GLuint VAOID) const
  {
    return m_VBOIDs.at(buffType).at(VAOID);     // Returns the buffer of provided type and VAO id
  }

  void
  RendererBase::UpdateIndicesData(GLuint indicesVBOID, std::vector<int>& indices) const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,       // Bind VBO with provided id, being an element array buffer
                 indicesVBOID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,    // Set the buffer data
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
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);       // Bind VBO with provided id, being an array buffer
    glBufferSubData(GL_ARRAY_BUFFER,            // Set the buffer data
                    0,
                    sizeof(float) * data.size(),
                    data.data());
    glVertexAttribPointer(layoutLocation,       // Configure layout for float values
                          numFloatsPerEntry,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (const GLvoid*)0);
    glEnableVertexAttribArray(layoutLocation);  // Enable layout
  }

  void
  RendererBase::UpdateArrayBufferDataInt(GLuint VBOID,
                                         std::vector<float>& data,
                                         int numFloatsPerEntry,
                                         int layoutLocation) const
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);       // Bind VBO with provided id, being an array buffer
    glBufferSubData(GL_ARRAY_BUFFER,            // Set the buffer data
                    0,
                    sizeof(int) * data.size(),
                    data.data());
    glVertexAttribIPointer(layoutLocation,      // Configure layout for int values
                           numFloatsPerEntry,
                           GL_INT,
                           0,
                           (const GLvoid*)0);
    glEnableVertexAttribArray(layoutLocation);  // Enable layout
  }

  void
  RendererBase::UpdateData(GLuint VBOID,
                           std::vector<float>& data,
                           BufferTypes buffType,
                           int layoutLocation) const
  {
    if (buffType == BufferTypes::BoneIDs)       // Does the buffer hold BoneID data=
    {
      UpdateArrayBufferDataInt(VBOID,           // If so, update buffer with int data
                               data,
                               RendererBase::k_numFloatsPerEntry.at(buffType),
                               layoutLocation);
    }
    else
    {
      UpdateArrayBufferData(VBOID,              // Else, update with float data
                            data,
                            RendererBase::k_numFloatsPerEntry.at(buffType),
                            layoutLocation);
    }
  }

  void
  RendererBase::UseVAOEnd() const
  {
    glBindVertexArray(0);                       // Unbind currently used VAO
    glUseProgram(0);                            // Stop using shader program
  }

  void
  RendererBase::CleanupBase() const
  {
    for (auto& buffType : m_VBOIDs)             // Loop through all keys of buffer types
    {
      for (auto& bufferEntry : buffType.second) // Loop through all keys of VAO ids
      {
        glDeleteBuffers(1,                      // Delete every VBO
                        &bufferEntry.second);
      }
    }

    for (auto VAOID : m_VAOIDs)                 // Loop through all VAO ids
    {
      glDeleteVertexArrays(1, &VAOID);          // And delete them
    }

    m_shaderProgram->Cleanup();                 // Finally, clean up shader proram
  }
}