#ifndef _RENDER_H_
#define _RENDER_H_

/// @brief runs only once at startup
void R_Init();

/// @brief clears screen buffers
void R_BeginFrame();

/// @brief swaps buffers
void R_EndFrame();

/// @brief renders a colored triangle
void Test_Polygon();

#endif