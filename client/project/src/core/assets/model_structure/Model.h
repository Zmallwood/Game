#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "core/assets/animation_structure/BoneInfo.h"

namespace Zmallwood
{
  class Model
  {
  public:
    /// Expects a filepath to a 3D model.
    Model(std::string const& path, bool gamma = false);
    /// Draws the model, and thus all its meshes
    void Draw();
    auto& BoneInfoMap() { return m_boneInfoMap; }
    int& BoneCount() { return m_boneCounter; }

    // Model data
    std::vector<Texture>
      texturesLoaded; ///< stores all the textures loaded so far,
                      ///< optimization to make sure textures aren't
                      ///< loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

  private:
    /// Loads a model with supported ASSIMP extensions from file and stores the
    /// resulting meshes in the meshes vector.
    void LoadModel(std::string const& path);
    /// Processes a node in a recursive fashion. Processes each individual mesh
    /// located at the node and repeats this process on its children nodes (if
    /// any).
    void ProcessNode(aiNode* node, const aiScene* scene);
    void SetVertexBoneDataToDefault(GLMVertex& vertex);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(GLMVertex& vertex, int boneID, float weight);
    void ExtractBoneWeightForVertices(std::vector<GLMVertex>& vertices,
                                      aiMesh* mesh,
                                      const aiScene* scene);
    unsigned int TextureFromFile(const char* path,
                                 const std::string& directory,
                                 bool gamma = false);
    /// Checks all material textures of a given type and loads the textures if
    /// they're not loaded yet. the required info is returned as a Texture
    /// struct.
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat,
                                              aiTextureType type,
                                              std::string typeName);

    std::map<std::string, BoneInfo> m_boneInfoMap;
    int m_boneCounter = 0;
  };
}