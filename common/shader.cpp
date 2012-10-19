
#include "shader.h"

namespace GLES2
{

Shader::Shader(const GLchar** source, GLuint shaderType)
    : m_compiled(false)
{
    m_shader = glCreateShader(shaderType);
    if (m_shader == 0)
        return; // TODO handle error

    glShaderSource(m_shader, 1, source, 0);
    glCompileShader(m_shader);
    GLint compiled;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compiled);
    m_compiled = compiled != GL_FALSE;

    if (!m_compiled) {
        glDeleteShader(m_shader);
        return;
    }
}

Shader::~Shader()
{
    if (m_shader != 0)
        glDeleteShader(m_shader);
}

void Shader::infoLog(GLchar* infoLog, GLsizei bufferLength, GLsizei *infoLength) const
{
    glGetShaderInfoLog(m_shader, static_cast<GLsizei>(bufferLength),
                       infoLength, infoLog);
}

}
