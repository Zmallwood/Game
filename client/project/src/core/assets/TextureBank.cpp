#include "TextureBank.h"

namespace Zmallwood {
  TextureBank::TextureBank() {
    LoadTextures();
  }

  void TextureBank::LoadTextures() {
    sf::Texture t1;
    t1.loadFromFile("./resources/images/Ground.png");
    m_images.insert({Hash("Ground"), t1});
  }

  void TextureBank::BindTexture(const std::string &imageName) {
    auto hash = Hash(imageName);
    if (m_images.contains(hash)) {
      sf::Texture::bind(&m_images.at(hash));
    }
  }

  void TextureBank::UnbindTexture() {
    sf::Texture::bind(NULL);
  }

  TextureBank *TextureBank::Get() {
    static TextureBank instance;
    return &instance;
  }
}