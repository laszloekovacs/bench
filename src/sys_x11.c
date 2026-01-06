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
    int attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};
    XVisualInfo *vi = glXChooseVisual(win->display, screen, attribs);

    if (!vi)
    {
        fprintf(stderr, "Failed to choose visual\n");
        XCloseDisplay(win->display);
        free(win);
        return NULL;
    }

    XSetWindowAttributes swa;
    swa.colormap = XCreateColormap(win->display, RootWindow(win->display, screen), vi->visual, AllocNone);
    swa.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    win->window = XCreateWindow(win->display, RootWindow(win->display, screen),
                                0, 0, width, height, 0, vi->depth, InputOutput,
                                vi->visual, CWColormap | CWEventMask, &swa);

    XSetStandardProperties(win->display, win->window, title, title, None, NULL, 0, NULL);

    win->context = glXCreateContext(win->display, vi, NULL, GL_TRUE);
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
        R_EndFrame();

        glXSwapBuffers(dpy, win);
    }
}
