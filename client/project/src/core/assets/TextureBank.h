#pragma once

namespace zw
{
  class TextureBank
  {
  public:
    void BindTexture(const std::string& imageName);
    void UnbindTexture();
    static TextureBank* Get();

  private:
    TextureBank();
    void LoadTextures();

    const std::string k_relImagesPath = "resources/images/";
    std::map<int, sf::Texture> m_textures;
  };
}