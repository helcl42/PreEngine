# PreEngine

### Description
PreEngine is simple rendering engine that is now available as VS2015(vc14) solution only(still not migrated to CMake). Solution provides example usage by containing Test project as part of solution.

### Dependencies
GLFW, Assimp, FreeImage, FreeType, GLM, OpenAL, Lua, jsoncpp

### Build
- download dependency pack from https://drive.google.com/file/d/0B-uBUwz6hRcWYVFQVGNxbkZSdzA/view?usp=sharing and extract it.

- define system variable PREENGINE_DEPENDENCIES_ROOT with path to previously downloaded dependecies

- set up Visual Leak detector by steps described here: https://vld.codeplex.com/

### Run
- download runtime dependencies only from https://drive.google.com/file/d/0B-uBUwz6hRcWSVA0SDBVNVYwVUk/view?usp=sharing and copy them to specific build folders