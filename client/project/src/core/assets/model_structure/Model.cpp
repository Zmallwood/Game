#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace zw
{
  Model::Model(std::string const& path, bool gamma)
    : gammaCorrection(gamma)
  {
    LoadModel(path);
  }

  void
  Model::Draw()
  {
    for (unsigned int i = 0; i < meshes.size(); i++)
        // meshes[i].Draw(shader);
      meshes[i].Draw();
  }

  void
  Model::LoadModel(std::string const& path)
  {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    { // if is Not Zero
      std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;

      return;
    }

    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene);
  }

  // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this
  // process on its children nodes (if any).
  void
  Model::ProcessNode(aiNode* node, const aiScene* scene)
  {
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      // the node object only contains indices to index the actual objects in the scene.
      // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(ProcessMesh(mesh, scene));
    }

    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
      ProcessNode(node->mChildren[i], scene);
  }

  void
  Model::SetVertexBoneDataToDefault(GLMVertex& vertex)
  {
    for (int i = 0; i < k_maxBoneInfluence; i++)
    {
      vertex.m_boneIDs[i] = -1;
      vertex.m_weights[i] = 0.0f;
    }
  }

  Mesh
  Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
  {
    std::vector<GLMVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      GLMVertex vertex;
      SetVertexBoneDataToDefault(vertex);
      vertex.position = AssimpGLMUtilities::GetGLMVec(mesh->mVertices[i]);
      vertex.normal = AssimpGLMUtilities::GetGLMVec(mesh->mNormals[i]);

      if (mesh->mTextureCoords[0])
      {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.texCoords = vec;
      }
      else
      {
        vertex.texCoords = glm::vec2(0.0f, 0.0f);
      }

      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];

      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    ExtractBoneWeightForVertices(vertices, mesh, scene);

    return Mesh(vertices, indices, textures);
  }

  void
  Model::SetVertexBoneData(GLMVertex& vertex, int boneID, float weight)
  {
    for (int i = 0; i < k_maxBoneInfluence; ++i)
    {
      if (vertex.m_boneIDs[i] < 0)
      {
        vertex.m_weights[i] = weight;
        vertex.m_boneIDs[i] = boneID;

        break;
      }
    }
  }

  void
  Model::ExtractBoneWeightForVertices(std::vector<GLMVertex>& vertices, aiMesh* mesh, const aiScene* scene)
  {
    auto& boneInfoMap = m_boneInfoMap;
    int& boneCount = m_boneCounter;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
      int boneID = -1;
      std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

      if (boneInfoMap.find(boneName) == boneInfoMap.end())
      {
        BoneInfo newBoneInfo;
        newBoneInfo.ID = boneCount;
        newBoneInfo.offset =
          AssimpGLMUtilities::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
        boneInfoMap[boneName] = newBoneInfo;
        boneID = boneCount;
        boneCount++;
      }
      else
      {
        boneID = boneInfoMap[boneName].ID;
      }

      assert(boneID != -1);
      auto weights = mesh->mBones[boneIndex]->mWeights;
      int numWeights = mesh->mBones[boneIndex]->mNumWeights;

      for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
      {
        int vertexId = weights[weightIndex].mVertexId;
        float weight = weights[weightIndex].mWeight;
        assert(vertexId <= vertices.size());
        SetVertexBoneData(vertices[vertexId], boneID, weight);
      }
    }
  }

//  unsigned int
//  Model::Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
//  {
//    std::string filename = std::string(path);
//    filename = directory + '/' + filename;
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//
//    if (data)
//    {
//      GLenum format;
//
//      if (nrComponents == 1)
//        format = GL_RED;
//      else if (nrComponents == 3)
//        format = GL_RGB;
//      else if (nrComponents == 4)
//        format = GL_RGBA;
//
//      glBindTexture(GL_TEXTURE_2D, textureID);
//      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//      glGenerateMipmap(GL_TEXTURE_2D);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//      stbi_image_free(data);
//    }
//    else
//    {
//      std::cout << "Texture failed to load at path: " << path << std::endl;
//      stbi_image_free(data);
//    }
//
//    return textureID;
//  }

  // checks all material textures of a given type and loads the textures if they're not loaded yet.
  // the required info is returned as a Texture struct.
  std::vector<Texture>
  Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
  {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
      aiString str;
      mat->GetTexture(type, i, &str);
      // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
      bool skip = false;

      for (unsigned int j = 0; j < texturesLoaded.size(); j++)
      {
        if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
        {
          textures.push_back(texturesLoaded[j]);
          skip = true; // a texture with the same filepath has already been loaded, continue to next one.
            // (optimization)
          break;
        }
      }

      if (!skip)
      { // if texture hasn't been loaded already, load it
        Texture texture;
        //texture.ID = TextureFromFile(str.C_Str(), this->directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        texturesLoaded.push_back(texture); // store it as texture loaded for entire model, to ensure we
          // won't unnecessary load duplicate textures.
      }
    }

    return textures;
  }
}