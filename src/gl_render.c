#include "common.h"
#include "render.h"
#include "stdio.h"

void R_Init()
{
    printf("GL VERSION: %s\n", glGetString(GL_VERSION));

    // Basic GL state
    glClearColor(0.9f, 0.1f, 0.15f, 1.0f);
    glDisable(GL_DEPTH_TEST);
}

void R_BeginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void R_EndFrame()
{
    // glXSwapBuffers(r_display, r_window);
}

void Test_Polygon()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);

    glEnd();
}
