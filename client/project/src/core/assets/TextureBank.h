#pragma once

namespace Zmallwood {
  class TextureBank {
   public:
    void BindTexture(const std::string &imageName);
    void UnbindTexture();
    static TextureBank *Get();

   private:
    TextureBank();
    void LoadTextures();

    std::map<int, sf::Texture> m_images;
  };
}