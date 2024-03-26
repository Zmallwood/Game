#include "Graphics.h"

namespace Funtasia {
    Graphics::Graphics() {
        {
            auto desktopMode = sf::VideoMode::getDesktopMode();
            
            auto settings = sf::ContextSettings();
            settings.depthBits = 24;

            m_renderWindow = std::make_shared<sf::RenderWindow>(
                desktopMode, "SFML OpenGL", sf::Style::Fullscreen,
                settings);
        }

        glClearDepth(1.f);
        glClearColor(0.3f, 0.3f, 0.3f, 0.f);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.f, 1.f, 1.f, 300.0f);  // fov, aspect, zNear, zFar
    }

    Graphics *Graphics::Get() {
        static Graphics instance;
        return &instance;
    }
}