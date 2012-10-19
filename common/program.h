
#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLES2/gl2.h>

#include "shader.h"

namespace GLES2
{

class Program
{
public:
    Program(VertexShader *vertexShader, FragmentShader *fragmentShader);
    ~Program();

    GLuint program() const { return m_program; }
    void use();

    FragmentShader fragmentShader() const;
    VertexShader vertexShader() const;

protected:
    virtual void bindAttributes() { }

private:
    bool link();

    GLuint m_program;
    VertexShader *m_vertexShader;
    FragmentShader *m_fragmentShader;
};

}

#endif // PROGRAM_H
