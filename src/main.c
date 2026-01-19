#include "common.h"

int running = 1;

int main(int argc, char **argv)
{
    /* init console so the subsystems can write to it */
    Con_Init();

    /* console variables */

    /* console commands */

    /* parse lauch arguments */
    Arg_Init(argc, argv);

    /* timer and performance timers */
    Timer_Init();

    /* asset streaming system */

    /* x windowing system */

    /* graphics */

    /* input handling */

    /* sound */

    while (running)
    {
        /* server side */

        /* client side */
        Client_Frame();
    }

    /* resource cleanup */

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