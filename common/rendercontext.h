
#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <EGL/egl.h>

class RenderContext
{
public:
    RenderContext(EGLint attribList[]);
    ~RenderContext();

    bool makeCurrent();
    bool swapBuffers();

protected:
    RenderContext() { }
    virtual EGLSurface createSurface() = 0;

    EGLDisplay m_display;
    EGLContext m_context;
    EGLSurface m_surface;
    EGLConfig m_config;
    EGLNativeWindowType m_window;
};

#endif // RENDERCONTEXT_H
