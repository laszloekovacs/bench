/* struct definitions for engine level stuff only */

#ifndef _DEFS_H_
#define _DEFS_H_

// disable padding
#pragma pack(push, 1)

/* Math Constants */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Conversion Macros */
// Multiplies by PI/180
#define TO_RAD(deg) ((deg) * (M_PI / 180.0))

// Multiplies by 180/PI
#define TO_DEG(rad) ((rad) * (180.0 / M_PI))

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

// plane def. could also be represented with 4 component vector?
typedef struct
{
    vec3_t point;
    vec3_t normal;
} plane_t;

typedef struct
{
    vec3_t position;
    vec3_t target;

    vec3_t right;
    vec3_t up;

    float yaw;
    float pitch;
    float roll;

    // final calculated mtx
    mat4_t view_matrix;
} view_t;

// identity matrix
#define MAT4_IDENTITY {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}

// disable padding
#pragma pack(pop)
#endif