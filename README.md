# PreEngine

### Description
PreEngine is simple rendering engine that is now available as VS2015(vc14) solution only(still not migrated to CMake). Solution contains example(Test project) with shown usage.

### Dependencies
GLFW, Assimp, FreeImage, FreeType, GLM, OpenAL, Lua, JsonCpp

### Build
- download dependency pack from https://drive.google.com/open?id=0B-uBUwz6hRcWSmstSDc2T0hnbEk and extract it

- define system variable PREENGINE_DEPENDENCIES_ROOT with path to previously downloaded dependecies

- for DEBUG build set up Visual Leak detector by steps described here: https://vld.codeplex.com/

### Run
- download runtime dependencies only https://drive.google.com/open?id=0B-uBUwz6hRcWenAtd0JaZ09kRnc and copy them to specific build folders
