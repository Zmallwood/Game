#pragma once
#include "Texture.h"

namespace Zmallwood
{
  class Mesh
  {
  public:
    Mesh(std::vector<GLMVertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<Texture> textures);
    void Draw(void);

    // Mesh Data
    std::vector<GLMVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

  private:
    /// Initializes all the buffer objects/arrays
    void SetupMesh();

    unsigned int m_VBO;
    unsigned int m_EBO;
  };
}