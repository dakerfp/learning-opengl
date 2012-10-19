
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

    void draw();

protected:
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
    EGLConfig config;
    EGLNativeWindowType window;
};

#endif // RENDERCONTEXT_H
