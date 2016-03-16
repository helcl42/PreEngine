# PreEngine

### Description
PreEngine is simple rendering engine that is now available as VS solution only(still not migrated to CMake). Solution provides example usage by containing Test project as part of solution.
On Windows platform it is tested in VS2013(vc12), so do not hesitate to let me know about build or any other relevant problem. 

### Dependencies
GLFW, Assimp, FreeImage, FreeType, GLM, OpenAL, Lua, jsoncpp

### Build
- download dependency pack from https://drive.google.com/file/d/0B-uBUwz6hRcWMXE2M0NqZjd6YUE/view?usp=sharing and extract it.

- define system variable PREENGINE_DEPENDENCIES_ROOT with path to previously downloaded dependecies

- set up Visual Leak detector by steps described here: https://vld.codeplex.com/

### Run
- download runtime dependencies only from https://drive.google.com/file/d/0B-uBUwz6hRcWUThJOFI0b2JxZkU/view?usp=sharing and copy them to specific build folders