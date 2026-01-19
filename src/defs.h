/* struct definitions for engine level stuff only */

#ifndef _DEFS_H_
#define _DEFS_H_

// disable padding
#pragma pack(push, 1)

typedef union
{
    struct
    {
        float x, y, z;
    };
    float v[3];
} vec3_t;

typedef union
{
    struct
    {
        float x, y, z, w;
    };
    float v[4];
} vec4_t;

/* column major order, as in glsl, eg. m[1][0] = second column, first row */
typedef struct
{
    float m[4][4];
} mat4_t;

// identity matrix
#define MAT4_IDENTITY {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}

// disable padding
#pragma pack(pop)
#endif