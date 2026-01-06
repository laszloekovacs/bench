#include "common.h"

int main()
{

    GLWindow *gv = x11_gl_window_create("bench", 600, 400);
    fprintf(stderr, "init renderer\n");
    R_Init();
    run_event_loop(gv->display, gv->window);

    return 0;
}