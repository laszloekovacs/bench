#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "stdbool.h"

#include "render.h"

GLWindow *x11_gl_window_create(const char *title, int width, int height)
{
    GLWindow *win = malloc(sizeof(GLWindow));

    win->display = XOpenDisplay(NULL);
    if (!win->display)
    {
        fprintf(stderr, "Failed to open X11 display\n");
        free(win);
        return NULL;
    }

    int screen = DefaultScreen(win->display);
    // int attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};
    /*
        XVisualInfo *vi = glXChooseVisual(win->display, screen, attribs);

        if (!vi)
        {
            fprintf(stderr, "Failed to choose visual\n");
            XCloseDisplay(win->display);
            free(win);
            return NULL;
        }
    */

    int fb_attribs[] = {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        None};

    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(win->display, screen, fb_attribs, &fbcount);
    GLXFBConfig fbconfig = fbc[0];

    XVisualInfo *vi = glXGetVisualFromFBConfig(win->display, fbconfig);

    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(win->display, RootWindow(win->display, screen), vi->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    win->window = XCreateWindow(win->display, RootWindow(win->display, screen),
                                0, 0, width, height, 0, vi->depth, InputOutput,
                                vi->visual, CWColormap | CWEventMask, &swa);

    XSetStandardProperties(win->display, win->window, title, title, None, NULL, 0, NULL);

    /*
    win->context = glXCreateContext(win->display, vi, NULL, GL_TRUE);
   */
    // Load the extension function
    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
        (void *)glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

    // Attributes for a legacy 2.1 compatibility context
    int ctx_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
        GLX_CONTEXT_MINOR_VERSION_ARB, 1,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        None};

    win->context = glXCreateContextAttribsARB(win->display, fbconfig, 0, True, ctx_attribs);
    // glXMakeCurrent(r_display, r_window, r_context);

    glXMakeCurrent(win->display, win->window, win->context);

    XMapWindow(win->display, win->window);
    XFree(vi);

    return win;
}

void x11_gl_window_destroy(GLWindow *win)
{
    if (win)
    {
        glXDestroyContext(win->display, win->context);
        XDestroyWindow(win->display, win->window);
        XCloseDisplay(win->display);
        free(win);
    }
}

void run_event_loop(Display *dpy, Window win)
{
    XEvent event;
    bool running = true;

    while (running)
    {
        while (XPending(dpy))
        {
            XNextEvent(dpy, &event);

            switch (event.type)
            {
            case DestroyNotify:
                running = false;
                break;

            case ClientMessage:
                running = false;
                break;

            case KeyPress:
                // Optional: handle keyboard input
                break;
            }
        }

        // Optional: render OpenGL here
        R_BeginFrame();
        Test_Polygon();
        R_EndFrame();

        glXSwapBuffers(dpy, win);
    }
}
