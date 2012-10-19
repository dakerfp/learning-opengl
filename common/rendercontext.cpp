
#include "rendercontext.h"

#include <cassert>

RenderContext::RenderContext(EGLint attribList[])
{
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint numConfigs;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(m_display != EGL_NO_DISPLAY);
    assert(eglGetError() == EGL_SUCCESS);

    // Initialize EGL
    assert(eglInitialize(m_display, &majorVersion, &minorVersion));
    assert(eglGetError() == EGL_SUCCESS);

    // Get configs
    assert(eglGetConfigs(m_display, NULL, 0, &numConfigs));
    assert(eglGetError() == EGL_SUCCESS);

    // Choose config
    assert(eglChooseConfig(m_display, attribList, &m_config, 1, &numConfigs));
    assert(eglGetError() == EGL_SUCCESS);

    // Create context
    m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, NULL);
    assert(m_context != EGL_NO_CONTEXT);
    assert(eglGetError() == EGL_SUCCESS);

    // Create surface
    m_surface = createSurface();
    assert(m_surface != EGL_NO_SURFACE);
    assert(eglGetError() == EGL_SUCCESS);
}

RenderContext::~RenderContext()
{
    makeCurrent();
    eglDestroySurface(m_display, m_surface);
    eglDestroyContext(m_display, m_context);
    eglTerminate(m_display);
}

bool RenderContext::swapBuffers()
{
    return eglSwapBuffers(m_display, m_surface);
}

bool RenderContext::makeCurrent()
{
    return eglMakeCurrent(m_display, m_surface, m_surface, m_context);
}
