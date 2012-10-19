
#ifndef SHADER_H
#define SHADER_H

#include <GLES2/gl2.h>

namespace GLES2
{

class Shader
{
public:
    Shader(const GLchar** source, GLuint shader);
    ~Shader();

    GLint shader() const { return m_shader; }
    bool compiled() const { return m_compiled; }
    virtual GLuint type() const = 0;

    void infoLog(GLchar* infoLog, GLsizei bufferLength, GLsizei *infoLength) const;

private:
    GLint m_shader;
    bool m_compiled;
};

class VertexShader : public Shader
{
public:
    VertexShader(const GLchar** source) : Shader(source, GL_VERTEX_SHADER) { }

    GLuint type() const { return GL_VERTEX_SHADER; }
};

class FragmentShader : public Shader
{
public:
    FragmentShader(const GLchar** source) : Shader(source, GL_FRAGMENT_SHADER) { }

    GLuint type() const { return GL_FRAGMENT_SHADER; }
};

}

#endif // SHADER_H
