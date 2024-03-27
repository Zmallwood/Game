#include "ImageBank.h"

namespace Zmallwood {
    ImageBank::ImageBank() {
        LoadImages();
    }

    void ImageBank::LoadImages() {
        sf::Texture t1;
        t1.loadFromFile("./resources/images/Ground.png");
        m_images.insert({Hash("Ground"), t1});
    }
    
    void ImageBank::BindImage(const std::string &imageName) {
        auto hash = Hash(imageName);
        if (m_images.contains(hash)) {
            sf::Texture::bind(&m_images.at(hash));
        }
    }

    ImageBank *ImageBank::Get() {
        static ImageBank instance;
        return &instance;
    }
}