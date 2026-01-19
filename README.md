# simple opengl renderer

## plans / ideas: 
- multiplatform: windows, linux, freebsd
- low system requirements. 
- target hardware around 2005-2008 +60fps on radeon hd 4850 / athlon 64 / 512mb on *nix
- optional pipeline. sse2, opencl, opengl 2.1, shaders / ffp , software?
- optimizations like aabb-s, hbvs
- Path tracing, ray marching?
- level of detail system
- athmosperic and camera effects
- simplified, fast implementaton of effects 
- user controlled camera
- diagnostics, metrics, benchmarking
- streaming assets models / textures / texture atlasses
- openAL dynamic sound
- web based editor in react / threejs?
- long distance rendering / multi layer
- matcap shading


system headers should all go into one and modules should include only one, eg common.h where most definitions should reside.

common should include the type definitions from defs.h and also define all low level, os dependent engine type function declarations.

use getopt to indicate what world file to load, or what server to connect to.