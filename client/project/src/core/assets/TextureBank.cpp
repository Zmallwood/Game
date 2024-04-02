#include "TextureBank.h"

namespace zw
{
  TextureBank::TextureBank()
  {
    LoadTextures();                             // Load textures from filesystem on object reation
  }

  void
  TextureBank::LoadTextures()
  {
    using iterator = std::filesystem ::recursive_directory_iterator;
    auto allTexturesPath = std::filesystem::current_path().string() + "/" + k_relImagesPath;

    for (auto& entry : iterator(allTexturesPath))
    {
      auto absPath = entry.path().string();

      if (FileExtension(absPath) != "png")
      {
        continue;
      }
      {
        sf::Texture t;
        t.loadFromFile(absPath);
        auto modelName = FilenameNoExtension(absPath);
        m_textures.insert({ Hash(modelName), t });
      }
    }
  }

  void
  TextureBank::BindTexture(const std::string& imageName)
  {
    auto hash = Hash(imageName);                // Convert image name to hash code
    if (m_textures.contains(hash))              // Check if texture exists
    {
      sf::Texture::bind(&m_textures.at(hash));  // If so, bind it for use with OpenGL
    }
  }

  void
  TextureBank::UnbindTexture()
  {
    sf::Texture::bind(NULL);
  }

  TextureBank*
  TextureBank::Get()
  {
    static TextureBank instance;                // Create singleton instance once
    return &instance;
  }
}