#pragma once

namespace Zmallwood {
    class ImageBank {
       public:
        void BindImage(const std::string &imageName);
        static ImageBank *Get();

       private:
        ImageBank();
        void LoadImages();

        std::map<int, sf::Texture> m_images;
    };
}