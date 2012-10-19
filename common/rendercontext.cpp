
#include "rendercontext.h"

#include <cassert>

RenderContext::RenderContext(EGLint attribList[])
{
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint numConfigs;

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display != EGL_NO_DISPLAY);
    assert(eglGetError() == EGL_SUCCESS);

    // Initialize EGL
    assert(eglInitialize(display, &majorVersion, &minorVersion));
    assert(eglGetError() == EGL_SUCCESS);

    // Get configs
    assert(eglGetConfigs(display, NULL, 0, &numConfigs));
    assert(eglGetError() == EGL_SUCCESS);

    // Choose config
    assert(eglChooseConfig(display, attribList, &config, 1, &numConfigs));
    assert(eglGetError() == EGL_SUCCESS);

    // Create context
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
    assert(context != EGL_NO_CONTEXT);
    assert(eglGetError() == EGL_SUCCESS);
}

RenderContext::~RenderContext()
{
}

bool RenderContext::swapBuffers()
{
    return eglSwapBuffers(display, surface);
}

bool RenderContext::makeCurrent()
{
    return eglMakeCurrent(display, surface, surface, context);
}

void RenderContext::draw()
{
}
