#ifndef COMMON_H
#define COMMON_H

// Memory leak debugger
#ifdef _DEBUG
	#include <vld.h> 
#endif

#include <cstdlib>
#include <time.h>
#include <mutex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <inttypes.h>
#include <array>
#include <list>
#include <set>
#include <thread>
#include <iomanip>
#include <typeindex>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE 
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF 

#include "../OpenGL/gl_core_4_4.h"
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

#include "IDGenerator.h"
#include "../Utils/GL/GLUtils.h"
#include "../Utils/StringUtils.h"
#include "../Utils/IO/File.h"
#include "../Utils/Log/Logger.h"
#include "../Utils/Math/Common.h"

#define SAFE_DELETE(pointer)       { if(pointer) { delete (pointer);     (pointer) = NULL; } }
#define SAFE_DELETE_ARRAY(pointer) { if(pointer) { delete[] (pointer);   (pointer) = NULL; } }
#define SAFE_RELEASE(pointer)      { if(pointer) { (pointer)->Release(); (pointer) = NULL; } }

#define PI 3.141592653589793
#define PI_F 3.1415927f
#define TWO_PI 6.2831853071795862
#define TWO_PI_F 6.2831853f

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#ifdef _UNICODE
#include <tchar.h>
#endif

#endif