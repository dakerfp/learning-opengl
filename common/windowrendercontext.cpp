
#include "windowrendercontext.h"

#include <cassert>

WindowRenderContext::WindowRenderContext(EGLint w, EGLint h,
    EGLNativeWindowType window, EGLint attribList[])
    : RenderContext(attribList)
    , m_window(window)
    , m_width(w)
    , m_height(h)
{

}

EGLSurface WindowRenderContext::createSurface()
{
    return eglCreateWindowSurface(m_display, m_config, m_window, NULL);
}

WindowRenderContext::~WindowRenderContext()
{
}
