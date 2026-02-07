# C++ Game Kit
A simple C++ framework for game development.  
Use it to develop your next game or as a learning resource for building something bigger.  

Written in C++20 using MSVC for Windows 10.  
Should be easy to port to other platforms.

## Building
* Requires VS2022 and Python to be installed
* Run ```build.py```
* Set working directory to ```GameDir```
* Run ```Game```
  
## Features
* <b>Core</b>
  * INI file reading/writing
  * Simple binary archive
  * Alarm event system
  * Fixed-timestep clock
* <b>OS</b>
  * Window management
  * Keyboard, mouse and gamepad input
* <b>Math</b>
  * Vector 2D
  * Vector 3D
  * Vector 4D
  * Matrix 4x4
  * Quaternion
  * Transformation
  * 2D Collision
    * AABB
    * Circle
  * 3D Collision
    * AABB
    * Sphere
* <b>Rendering</b>
  * Shader manager
  * Framebuffer manager
  * Out-of-the-box 2D rendering pipeline
    * Sprite rendering
    * Sprite atlas rendering
    * Sprite sheet animation
    * Sprite font rendering
    * Hardware instancing
  * 3D Model loading
  * 3D Scene setup

## Third-party libraries used:
* [stb_image](https://github.com/nothings/stb)
* [SoLoud](https://solhsa.com/soloud/)
* [SDL3](https://github.com/libsdl-org/SDL)
* [bgfx](https://github.com/bkaradzic/bgfx)
* [assimp](https://github.com/assimp/assimp)
