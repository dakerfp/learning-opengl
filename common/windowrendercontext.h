#ifndef WINDOWRENDERCONTEXT_H
#define WINDOWRENDERCONTEXT_H

#include "rendercontext.h"

class WindowRenderContext : public RenderContext
{
public:
    WindowRenderContext(EGLint width, EGLint height,
        EGLNativeWindowType nwt, EGLint attribList[]);
    ~WindowRenderContext();

protected:
    EGLSurface createSurface();

private:
    EGLNativeWindowType m_window;
    EGLint m_width;
    EGLint m_height;
};

#endif // WINDOWRENDERCONTEXT_H
