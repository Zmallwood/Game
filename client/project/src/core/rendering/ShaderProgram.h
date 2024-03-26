#pragma once

namespace Zmallwood {
    class ShaderProgram {
       public:
        bool Create(const GLchar *vertexShaderSource,
                    const GLchar *fragmentShaderSource);
        void Cleanup();
        auto ProgramID() const { return m_programID; }

       private:
        GLuint CompileShader(const GLchar *shaderSource, GLuint *shader,
                             GLenum shaderType);

        GLuint m_programID = 0;
    };
}