#include "TextureBank.h"

namespace Zmallwood
{
  TextureBank::TextureBank()
  {
    LoadTextures();                             // Load textures from filesystem on object reation
  }

  void
  TextureBank::LoadTextures()
  {
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/Ground.png");
      m_textures.insert({ Hash("Ground"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1_2.png");
      m_textures.insert({ Hash("ObjectTypeTree1_2"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1_2.png.001.png");
      m_textures.insert({ Hash("ObjectTypeTree1_2.png.001"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1_2.png.png");
      m_textures.insert({ Hash("ObjectTypeTree1_2.png"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1.png");
      m_textures.insert({ Hash("ObjectTypeTree1"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1.png.001.png");
      m_textures.insert({ Hash("ObjectTypeTree1.png.001"), t1 });
    }
    {
      sf::Texture t1;
      t1.loadFromFile("./resources/images/ObjectTypeTree1.png.png");
      m_textures.insert({ Hash("ObjectTypeTree1.png"), t1 });
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