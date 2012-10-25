
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#define WINDOW_RGB           0
#define WINDOW_ALPHA         1
#define WINDOW_DEPTH         2
#define WINDOW_STENCIL       4
#define WINDOW_MULTISAMPLE   8

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


RenderContext::RenderContext(EGLint attribList[])
{
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint numConfigs;

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY || eglGetError() != EGL_SUCCESS)
    {
        exit(-1);
    }

   // Initialize EGL
   if (!eglInitialize(display, &majorVersion, &minorVersion) || eglGetError() != EGL_SUCCESS)
   {
        exit(-1);
   }

   // Get configs
   if (!eglGetConfigs(display, NULL, 0, &numConfigs) || eglGetError() != EGL_SUCCESS)
   {
      exit(-1);
   }

   // Choose config
   if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs) || eglGetError() != EGL_SUCCESS)
   {
      exit(-1);
   }

   // Create context
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
   if (context == EGL_NO_CONTEXT || eglGetError() != EGL_SUCCESS)
   {
       exit(-1);
   }
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

class WindowRenderContext : public RenderContext
{
public:
    WindowRenderContext(EGLint width, EGLint height,
        EGLNativeWindowType nwt, EGLint attribList[]);
    ~WindowRenderContext();

private:
    EGLint width, height;
};

WindowRenderContext::WindowRenderContext(EGLint w, EGLint h,
    EGLNativeWindowType window, EGLint attribList[])
    : RenderContext(attribList)
    , width(w)
    , height(h)
{
    surface = eglCreateWindowSurface(display, config, window, NULL);
    if (surface == EGL_NO_SURFACE || eglGetError() != EGL_SUCCESS)
        exit(-1);
}

WindowRenderContext::~WindowRenderContext()
{
    makeCurrent();
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}


class XWindowRenderContext : public WindowRenderContext
{
public:
    XWindowRenderContext(int width, int height, const char *title, EGLint attrib_list[]);
    ~XWindowRenderContext()
    {
    }
};

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>

#define TRUE 1
#define FALSE 0

static EGLNativeWindowType WinCreate(int width, int height, const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    Display *x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return 0;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               x_display, root,
               0, 0, width, height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
       x_display,
       DefaultRootWindow ( x_display ),
       FALSE,
       SubstructureNotifyMask,
       &xev );

    return (EGLNativeWindowType) win;
}

XWindowRenderContext::XWindowRenderContext(int width, int height, const char *title, EGLint attrib_list[])
    : WindowRenderContext(width, height, WinCreate(width, height, title), attrib_list)
{
}

static EGLint attrib_list[] = {
    EGL_ALPHA_SIZE, 0,
    EGL_RED_SIZE, 5,
    EGL_GREEN_SIZE, 6,
    EGL_BLUE_SIZE, 5,
    EGL_DEPTH_SIZE, 16,
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_NONE
};


class MainWindow : public XWindowRenderContext
{
public:
    MainWindow()
        : XWindowRenderContext(480, 360, "Main", attrib_list)
    {
    }

    void draw()
    {
        glClearColor(0, 0.5, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main(int argc, char **argv)
{

    MainWindow context;
    context.makeCurrent();
    context.draw();
    context.swapBuffers();

    sleep(10);

    return EXIT_SUCCESS;
}
