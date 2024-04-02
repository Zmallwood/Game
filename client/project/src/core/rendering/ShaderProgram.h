#pragma once

namespace zw
{
  class ShaderProgram
  {
  public:
    bool Create(const GLchar* vertexShaderSource,
                const GLchar* fragmentShaderSource);
    void Cleanup();
    auto ProgramID() { return m_programID; }

  private:
    GLuint CompileShader(const GLchar* shaderSource,
                         GLuint* shader,
                         GLenum shaderType);

    GLuint m_programID = 0;
  };
}