#include "common.h"

int running = 1;

int main(int argc, char **argv)
{
    Arg_Init(argc, argv);
    Con_Init();
    Timer_Init();

    while (running)
    {
        Client_Frame();
    }

    return 0;
}

/*
int main(int argc, char **argv)
{

    GLWindow *gv = x11_gl_window_create("bench", 600, 400);
    fprintf(stderr, "init renderer\n");
    R_Init();
    run_event_loop(gv->display, gv->window);

    return 0;
}


*/