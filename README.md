# PreEngine

### Description
PreEngine is simple rendering engine that is now available as VS2015(vc14) solution only(still not migrated to CMake). Solution provides example usage in Test project which is part of the solution.

### Dependencies
GLFW, Assimp, FreeImage, FreeType, GLM, OpenAL, Lua, jsoncpp

### Build
- download dependency pack from https://drive.google.com/file/d/0B-uBUwz6hRcWVTVESmF0Z2xkUDA/view?usp=sharing and extract it.

- define system variable PREENGINE_DEPENDENCIES_ROOT with path to previously downloaded dependecies

- for DEBUG build set up Visual Leak detector by steps described here: https://vld.codeplex.com/

### Run
- download runtime dependencies only from https://drive.google.com/file/d/0B-uBUwz6hRcWNDBHMUM1QkRXSVk/view?usp=sharing and copy them to specific build folders
