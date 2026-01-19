
#include "common.h"
#include <stdarg.h>

/*
   console should be a ringbuffer of string pointers.
    Con_Print inserts a string into the ringbuffer.

 */
#define CON_MAX_LINES 1024
#define CON_MAX_LINE_LENGTH 1024
static char *con_lines[CON_MAX_LINES];
static int con_head = 0; // next insertion index static int con_count = 0; // number of valid lines

/// @brief call as soon as possible on startup
void Con_Init(void)
{
    for (int i = 0; i < CON_MAX_LINES; i++)
        con_lines[i] = NULL;

    con_head = 0;
    con_count = 0;
}

/// @brief inserts a new string into ringbuffer
void Con_Print(char *str)
{
    if (!str)
        return;

    // Free old line if overwriting
    if (con_lines[con_head])
    {
        free(con_lines[con_head]);
        con_lines[con_head] = NULL;
    }

    // Allocate and copy
    size_t len = strlen(str);
    if (len > CON_MAX_LINE_LENGTH - 1)
        len = CON_MAX_LINE_LENGTH - 1;

    char *line = malloc(len + 1);
    memcpy(line, str, len);
    line[len] = '\0';

    con_lines[con_head] = line;

    // Advance ring buffer
    con_head = (con_head + 1) % CON_MAX_LINES;
    if (con_count < CON_MAX_LINES)
        con_count++;
}

/// @brief print with formatting support
void Con_Printf(const char *fmt, ...)
{
    char buffer[CON_MAX_LINE_LENGTH];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    Con_Print(buffer);
}
