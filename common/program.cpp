
#include "program.h"

#include <cassert>

namespace GLES2
{

Program::Program(VertexShader *vertexShader, FragmentShader *fragmentShader)
    : m_vertexShader(vertexShader)
    , m_fragmentShader(fragmentShader)
{
    assert(vertexShader);
    assert(fragmentShader);

    m_program = glCreateProgram();

    glAttachShader(m_program, vertexShader->shader());
    glAttachShader(m_program, fragmentShader->shader());

    bindAttributes();

    if (!link())
    {
        glDeleteProgram(m_program);
    }
}

void Program::use()
{
    return glUseProgram(m_program);
}

bool Program::link()
{
    GLint linked;
    glLinkProgram(m_program);
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);

    return linked != GL_FALSE;
}

Program::~Program()
{
    if (m_program != 0)
        glDeleteProgram(m_program);
}

}
