#include "Graphics.h"

namespace zw
{
  Graphics::Graphics()
  {
    {
      auto desktopMode = sf::VideoMode::getDesktopMode();

      auto settings = sf::ContextSettings();
      settings.depthBits = 24;

      m_renderWindow =
        std::make_shared<sf::RenderWindow>(desktopMode, "SFML OpenGL", sf::Style::Fullscreen, settings);
    }

    glewExperimental = GL_TRUE;
    {
      auto glewError = glewInit();

      if (glewError != GLEW_OK)
        std::cout << "Error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
    }

    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 300.0f); // fov, aspect, zNear, zFar
  }

  void Graphics::Start2DRendering()
  {
    m_renderWindow = Graphics::Get()->RenderWindow();
    m_renderWindow->pushGLStates();
    m_renderWindow->resetGLStates();
  }

  void Graphics::Stop2DRendering()
  {
    m_renderWindow->popGLStates();
  }

  void Graphics::PresentCanvas()
  {
    m_renderWindow->display();
  }

  Graphics* Graphics::Get()
  {
    static Graphics instance;
    return &instance;
  }
}