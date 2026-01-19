#ifndef _COMMON_H_
#define _COMMON_H_

#define CL_TARGET_OPENCL_VERSION 300

#include <stdio.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <CL/cl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "render.h"

typedef struct
{
    Display *display;
    Window window;
    GLXContext context;
} GLWindow;

GLWindow *x11_gl_window_create(const char *title, int width, int height);
void x11_gl_window_destroy(GLWindow *win);
void run_event_loop(Display *dpy, Window win);

/* console */

void Con_Init(void);
void Con_Print(void);

#endif