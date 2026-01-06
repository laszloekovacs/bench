#include "common.h"

int main()
{

    GLWindow *gv = x11_gl_window_create("bench", 600, 400);

    run_event_loop(gv->display, gv->window);

    return 0;
}