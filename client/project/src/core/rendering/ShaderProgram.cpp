#include "ShaderProgram.h"

namespace Zmallwood
{
  bool
  ShaderProgram::Create(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
  {
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    m_programID = glCreateProgram();
    auto success = true;
    {
      auto vertexShaderRes = CompileShader(vertexShaderSource, &vertexShader, GL_VERTEX_SHADER);

      if (vertexShaderRes != GL_TRUE)
      {
        std::cout << "Unable to compile vertex shader.\n";
        success = false;
      }
    }

    if (success)
    {
      glAttachShader(m_programID, vertexShader);
      auto fragmentShaderRes = CompileShader(fragmentShaderSource, &fragmentShader, GL_FRAGMENT_SHADER);

      if (fragmentShaderRes != GL_TRUE)
      {
        std::cout << "Unable to compile fragment shader.\n";
        success = false;
      }
    }

    if (success)
    {
      glAttachShader(m_programID, fragmentShader);
      glLinkProgram(m_programID);
      GLint programSuccess = GL_TRUE;
      glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);

      if (programSuccess != GL_TRUE)
      {
        std::cout << "Error linking shader program.\n";
        success = false;
      }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return success;
  }

  void
  ShaderProgram::Cleanup()
  {
    glDeleteProgram(m_programID);
  }

  GLuint
  ShaderProgram::CompileShader(const GLchar* shaderSource, GLuint* shader, GLenum shaderType)
  {
    *shader = glCreateShader(shaderType);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderCompiled);

    return shaderCompiled;
  }
}