#include "IScene.h"
#include "core/Graphics.h"
#include "core/configuration/GameProps.h"

namespace Zmallwood
{
  IScene::IScene()
  {

    static bool initialized = false;

    if (!initialized)
    {

      glGenTextures(1, &m_texID);

      glGenFramebuffers(1, &m_FBO);
      glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
      glBindTexture(GL_TEXTURE_2D, m_texID);

      auto desktopMode = sf::VideoMode::getDesktopMode();
      auto canvW = desktopMode.width;
      auto canvH = desktopMode.height;
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, canvW, canvH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texID, 0);
      glGenRenderbuffers(1, &m_RBO);
      glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, canvW, canvH);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      glGenVertexArrays(1, &m_VAO);

      const std::string vertexShader = R"(
    #version 330 core

    layout (location = 0) in vec2 in_Position;
    layout (location = 1) in vec4 in_Color;
    layout (location = 2) in vec2 in_TexCoord;

    out vec4 ex_Color;
    out vec2 ex_TexCoord;
    out vec2 ex_Pos;

    void main() {
        gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
        ex_Color = in_Color;
        ex_TexCoord = in_TexCoord;
        ex_Pos = in_Position;
    }
                                       )";

      const std::string fragmentShader = R"(
    #version 330 core
    precision mediump float;

    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    in vec2 ex_Pos;
    uniform sampler2D TexUnit;
    //uniform float noPixelEffect;

    out vec4 fragColor;

    void main() {
        float r = 0.8;
        float xs = 1600*1.5;
        float ys = 900*1.5;
        int axis = 0;
        vec2 pos = ex_Pos;
        float x,y,rr=r*r,d,w,w0;
        vec2 p=0.5*(vec2(1.0,1.0)+pos);
        p = ex_TexCoord;
        vec4 col=vec4(0.0,0.0,0.0,0.0);
        w0=0.5135/pow(r,0.96);
        
        float noPixelEffect = 0.0;

        if (noPixelEffect == 0.0 && 1.0 != 0.0) {
            for (d=1.0/xs,x=-r,p.x+=x*d;x<=r;x++,p.x+=d){
                w=w0*exp((-x*x)/(2.0*rr));
                col+=texture(TexUnit,floor(p*500)/500)*w/2;
            }

            for (d=1.0/ys,y=-r,p.y+=y*d;y<=r;y++,p.y+=d){
                w=w0*exp((-y*y)/(2.0*rr));
                col+=texture(TexUnit,floor(p*300)/300)*w/2;
            }
        }
        else {
            for (d=1.0/xs,x=-r,p.x+=x*d;x<=r;x++,p.x+=d){
                w=w0*exp((-x*x)/(2.0*rr));
                col+=texture(TexUnit,p)*w/2;
            }

            for (d=1.0/ys,y=-r,p.y+=y*d;y<=r;y++,p.y+=d){
                w=w0*exp((-y*y)/(2.0*rr));
                col+=texture(TexUnit,p)*w/2;
            }
        }
        
        col.r = floor(col.r*10)/10;
        col.g = floor(col.g*10)/10;
        col.b = floor(col.b*10)/10;

        fragColor = col;
    }
                                         )";

      if (!m_shader.loadFromMemory(vertexShader, fragmentShader))
      {
        std::cout << "shader error\n";
      }

      glGenBuffers(1, &m_indexBufID);
      glGenBuffers(1, &m_posBufID);
      glGenBuffers(1, &m_colorBufID);
      glGenBuffers(1, &m_uvBufID);

      auto numVertices = 4;

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufID);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * 1 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, m_posBufID);
      glBufferData(GL_ARRAY_BUFFER, numVertices * 2 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, m_colorBufID);
      glBufferData(GL_ARRAY_BUFFER, numVertices * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, m_uvBufID);
      glBufferData(GL_ARRAY_BUFFER, numVertices * 2 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
      std::cout << "init\n";
      initialized = true;
    }

    m_gui = std::make_shared<tgui::Gui>(*Graphics::Get()->RenderWindow());
  }

  IScene::~IScene()
  {
    static bool cleanedUp = false;

    if (!cleanedUp)
    {
      glDeleteTextures(1, &m_texID);

      glDeleteFramebuffers(1, &m_FBO);
      glDeleteRenderbuffers(1, &m_RBO);

      glDeleteVertexArrays(1, &m_VAO);

      glDeleteBuffers(1, &m_indexBufID);
      glDeleteBuffers(1, &m_posBufID);
      glDeleteBuffers(1, &m_colorBufID);
      glDeleteBuffers(1, &m_uvBufID);
      std::cout << "cleanup\n";
      cleanedUp = true;
    }
  }

  void
  IScene::Render()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    {
      auto clearColorF = GameProps::Get()->ClearColor().ToColorF();
      glClearColor(clearColorF.r, clearColorF.g, clearColorF.b, clearColorF.a);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Render3D();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);




    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    




    auto numVertsInRect = 4;
    Vertex2F verts[numVertsInRect];
    auto color = Color{ .r = 255, .g = 255, .b = 255 };
    auto colorF = color.ToColorF();
    auto x = -1.0f;
    auto y = -1.0f;
    auto w = 2.0f;
    auto h = -2.0f;
    verts[0].position = { x, y - h };
    verts[1].position = { x, y };
    verts[2].position = { x + w, y };
    verts[3].position = { x + w, y - h };
    verts[0].uv = { 0.0f, 1.0f };
    verts[1].uv = { 0.0f, 0.0f };
    verts[2].uv = { 1.0f, 0.0f };
    verts[3].uv = { 1.0f, 1.0f };
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    auto indices = std::vector<int>(numVertsInRect);
    std::iota(std::begin(indices), std::end(indices), 0);
    std::vector<float> positions;
    std::vector<float> colors;
    std::vector<float> uvs;

    for (auto& vert : verts)
    {
      positions.push_back(vert.position.x);
      positions.push_back(vert.position.y);
      colors.push_back(colorF.r);
      colors.push_back(colorF.g);
      colors.push_back(colorF.b);
      colors.push_back(colorF.a);
      uvs.push_back(vert.uv.x);
      uvs.push_back(vert.uv.y);
    }

    sf::Shader::bind(&m_shader);
    glBindVertexArray(m_VAO);
    //glUniform1f(m_locNoPixelEffect, noPixelEffect ? 1.0f : 0.0f);

    const auto k_locPosition = 0;
    const auto k_locColor = 1;
    const auto k_locUv = 2;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(), indices.data());

    glBindBuffer(GL_ARRAY_BUFFER, m_posBufID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * positions.size(), positions.data());
    glVertexAttribPointer(k_locPosition, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(k_locPosition);

    glBindBuffer(GL_ARRAY_BUFFER, m_colorBufID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * colors.size(), colors.data());
    glVertexAttribPointer(k_locColor, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(k_locColor);

    glBindBuffer(GL_ARRAY_BUFFER, m_uvBufID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * uvs.size(), uvs.data());
    glVertexAttribPointer(k_locUv, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(k_locUv);

    glDrawElements(GL_TRIANGLE_FAN, numVertsInRect, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    sf::Shader::bind(NULL);
    {
      auto renderWindow = Graphics::Get()->RenderWindow();
      renderWindow->pushGLStates();
      renderWindow->resetGLStates();
      m_gui->draw();
      renderWindow->popGLStates();

      renderWindow->display();
    }
  }
}