#ifndef GL_UTILS_H
#define GL_UTILS_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace GL
		{
			class GLUtils
			{
			public:
				static std::string GetGLInfo();

				static std::string GetGLExtensionsInfo();

				static void InitDebugMode();

				static void InitGLFWDebugMode();

				static void GLFWDebugCallback(int error, const char* description);

				static void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* param);

				static int CheckForOpenGLError(const char * file, int line);

				static std::string GetShaderProgramInfo(GLuint shaderProgramHandle);

				static std::string GetShaderProgramInfoLog(GLuint shaderProgramHandle);

				static std::string GetShaderActiveAttributesInfo(GLuint shaderProgramHandle);

				static std::string GetShaderActiveUniformsInfo(GLuint shaderProgramHandle);

			private:
				static std::string ConvertErrorToString(GLenum error);

				static std::string ConvertSeverityToString(GLenum severity);

				static std::string ConvertSourceToString(GLenum source);

				static std::string ConvertTypeToString(GLenum type);

				static std::string ConvertShaderAttibuteToString(GLenum type);
			};
		}
	}
}
#endif