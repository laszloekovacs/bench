#include "common.h"
#include <string.h>
#include <stdlib.h>

static int arg_argc = 0;
static char **arg_argv = NULL;

void Arg_Init(int argc, char **argv)
{
    arg_argc = argc;
    arg_argv = argv;
}

/*
    Arg_Get("-width") → returns pointer to "1920"
    Arg_Get("-fullscreen") → returns "" (flag present)
    Arg_Get("-missing") → returns NULL
*/
char *Arg_Get(char *arg)
{
    if (!arg_argv || !arg)
        return NULL;

    for (int i = 0; i < arg_argc; i++)
    {
        if (strcmp(arg_argv[i], arg) == 0)
        {

            // If next argument exists and is not another flag, return it
            if (i + 1 < arg_argc && arg_argv[i + 1][0] != '-')
                return arg_argv[i + 1];

            // Flag present but no value
            return "";
        }
    }

    return NULL;
}
