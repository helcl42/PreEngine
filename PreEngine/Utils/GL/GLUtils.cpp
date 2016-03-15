#include "GLUtils.h"
#include "../Log/Logger.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace GL
		{
			std::string GLUtils::GetGLInfo()
			{
				const GLubyte* renderer = glGetString(GL_RENDERER);
				const GLubyte* vendor = glGetString(GL_VENDOR);
				const GLubyte* version = glGetString(GL_VERSION);
				const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

				GLint major, minor;
				glGetIntegerv(GL_MAJOR_VERSION, &major);
				glGetIntegerv(GL_MINOR_VERSION, &minor);

				std::stringstream ss;
				ss << "----------------------------------------------" << std::endl;
				ss << "GL Vendor: " << vendor << std::endl;
				ss << "GL Renderer: " << renderer << std::endl;
				ss << "GL Version: " << version << "(" << major << "." << minor << ")" << std::endl;
				ss << "GLSL Version: " << glslVersion << std::endl;
				ss << "----------------------------------------------" << std::endl;

				GLenum params[] =
				{
					GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
					GL_MAX_CUBE_MAP_TEXTURE_SIZE,
					GL_MAX_DRAW_BUFFERS,
					GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
					GL_MAX_TEXTURE_IMAGE_UNITS,
					GL_MAX_TEXTURE_SIZE,
					GL_MAX_VARYING_FLOATS,
					GL_MAX_VERTEX_ATTRIBS,
					GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
					GL_MAX_VERTEX_UNIFORM_COMPONENTS,
					GL_MAX_VIEWPORT_DIMS,
					GL_STEREO
				};

				const char* names[] =
				{
					"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
					"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
					"GL_MAX_DRAW_BUFFERS",
					"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
					"GL_MAX_TEXTURE_IMAGE_UNITS",
					"GL_MAX_TEXTURE_SIZE",
					"GL_MAX_VARYING_FLOATS",
					"GL_MAX_VERTEX_ATTRIBS",
					"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
					"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
					"GL_MAX_VIEWPORT_DIMS",
					"GL_STEREO",
				};

				for (int i = 0; i < 10; i++)
				{
					int v = 0;
					glGetIntegerv(params[i], &v);
					ss << names[i] << " - " << v << std::endl;
				}

				for (int i = 10; i < 11; i++)
				{
					int v[2];
					glGetIntegerv(params[i], v);
					ss << names[i] << " - " << v[0] << " x " << v[1] << std::endl;
				}

				for (int i = 11; i < 12; i++)
				{
					unsigned char s = 0;
					glGetBooleanv(params[i], &s);
					ss << names[i] << " - " << (unsigned int)s << std::endl;
				}

				ss << "----------------------------------------------" << std::endl;
				return ss.str();
			}

			std::string GLUtils::GetGLExtensionsInfo()
			{
				std::stringstream ss;
				GLint nExtensions;
				glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
				for (int i = 0; i < nExtensions; i++)
				{
					ss << glGetStringi(GL_EXTENSIONS, i) << std::endl;
				}

				return ss.str();
			}

			void GLUtils::InitGLFWDebugMode()
			{
				glfwSetErrorCallback(GLUtils::GLFWDebugCallback);
			}

			void GLUtils::GLFWDebugCallback(int error, const char* description)
			{
				PreEngine::Utils::Log::Logger::GetInstance().Debug() << "Errno: " << error << " -> " << description << std::endl;
			}

			void GLUtils::InitDebugMode()
			{
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(GLUtils::DebugCallback, NULL);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
				glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Start debugging");
			}

			void APIENTRY GLUtils::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* param)
			{
				std::string sourceStr = ConvertSourceToString(source);
				std::string typeStr = ConvertTypeToString(type);
				std::string sevStr = ConvertSeverityToString(severity);

				PreEngine::Utils::Log::Logger::GetInstance().Debug() << sourceStr << ":" << typeStr << "[" << sevStr << "] (" << id << "): " << msg << std::endl;
			}

			int GLUtils::CheckForOpenGLError(const char* file, int line)
			{
				int retCode = 0;
				GLenum glErr = glGetError();

				while (glErr != GL_NO_ERROR)
				{
					std::string message = ConvertErrorToString(glErr);
					PreEngine::Utils::Log::Logger::GetInstance().Error() << "glError in file " << " " << file << " " << " @ line " << line << ": " << message.c_str() << std::endl;
					retCode = 1;
					glErr = glGetError();
				}
				return retCode;
			}

			std::string GLUtils::ConvertErrorToString(GLenum error)
			{
				switch (error)
				{
				case GL_INVALID_ENUM: return "Invalid enum";
				case GL_INVALID_VALUE: return "Invalid value";
				case GL_INVALID_OPERATION: return "Invalid operation";
				case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid framebuffer operation";
				case GL_OUT_OF_MEMORY: return "Out of memory";
				default: return "Unknown error";
				}
				return "Unknown error";
			}

			std::string GLUtils::ConvertSeverityToString(GLenum severity)
			{
				switch (severity)
				{
				case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
				case GL_DEBUG_SEVERITY_MEDIUM: return "MED";
				case GL_DEBUG_SEVERITY_LOW: return "LOW";
				case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFY";
				default: return "UNK";
				}
				return "UNK";
			}

			std::string GLUtils::ConvertSourceToString(GLenum source)
			{
				switch (source)
				{
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WindowSys";
				case GL_DEBUG_SOURCE_APPLICATION: return "App";
				case GL_DEBUG_SOURCE_API: return "OpenGL";
				case GL_DEBUG_SOURCE_SHADER_COMPILER: return "ShaderCompiler";
				case GL_DEBUG_SOURCE_THIRD_PARTY: return "3rdParty";
				case GL_DEBUG_SOURCE_OTHER: return "Other";
				default: return "Unknown";
				}
				return "Unknown";
			}

			std::string GLUtils::ConvertTypeToString(GLenum type)
			{
				switch (type)
				{
				case GL_DEBUG_TYPE_ERROR: return "Error";
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated";
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined";
				case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
				case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
				case GL_DEBUG_TYPE_MARKER: return "Marker";
				case GL_DEBUG_TYPE_PUSH_GROUP: return "PushGroup";
				case GL_DEBUG_TYPE_POP_GROUP: return "PopGroup";
				case GL_DEBUG_TYPE_OTHER: return "Other";
				default: return "Unknown";
				}
				return "Unknown";
			}

			std::string GLUtils::ConvertShaderAttibuteToString(GLenum type)
			{
				switch (type)
				{
				case GL_BOOL: return "bool";
				case GL_INT: return "int";
				case GL_FLOAT: return "float";
				case GL_FLOAT_VEC2: return "vec2";
				case GL_FLOAT_VEC3: return "vec3";
				case GL_FLOAT_VEC4: return "vec4";
				case GL_FLOAT_MAT2: return "mat2";
				case GL_FLOAT_MAT3: return "mat3";
				case GL_FLOAT_MAT4: return "mat4";
				case GL_SAMPLER_2D: return "sampler2D";
				case GL_SAMPLER_3D: return "sampler3D";
				case GL_SAMPLER_CUBE: return "samplerCube";
				case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
				default: break;
				}
				return "other";
			}

			std::string GLUtils::GetShaderActiveAttributesInfo(GLuint shaderProgramHandle)
			{
				std::stringstream ss;
				int params = -1;
				glGetProgramiv(shaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &params);
				printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);

				for (int i = 0; i < params; i++)
				{
					char name[64];
					int maxLength = 64, actualLength = 0, size = 0;
					GLenum type;
					glGetActiveAttrib(shaderProgramHandle, i, maxLength, &actualLength, &size, &type, name);
					if (size > 1)
					{
						for (int j = 0; j < size; j++)
						{
							int location;
							std::stringstream longName;
							longName << name << "[" << j << "]";
							location = glGetAttribLocation(shaderProgramHandle, longName.str().c_str());
							ss << "  " << i << ") type:" << ConvertShaderAttibuteToString(type) << " name:" << longName.str() << " location:" << location << std::endl;
						}
					}
					else
					{
						int location = glGetAttribLocation(shaderProgramHandle, name);
						ss << "  " << i << ") type:" << ConvertShaderAttibuteToString(type) << " name:" << name << " location:" << location << std::endl;
					}
				}
				return ss.str();
			}

			std::string GLUtils::GetShaderActiveUniformsInfo(GLuint shaderProgramHandle)
			{
				std::stringstream ss;
				int params = -1;
				glGetProgramiv(shaderProgramHandle, GL_ACTIVE_UNIFORMS, &params);
				ss << "GL_ACTIVE_UNIFORMS = " << params << std::endl;
				for (int i = 0; i < params; i++)
				{
					char name[64];
					int maxLength = 64, actualLength = 0, size = 0;
					GLenum type;
					glGetActiveUniform(shaderProgramHandle, i, maxLength, &actualLength, &size, &type, name);
					if (size > 1)
					{
						for (int j = 0; j < size; j++)
						{
							int location;
							std::stringstream longName;
							longName << name << "[" << j << "]";
							location = glGetUniformLocation(shaderProgramHandle, longName.str().c_str());
							ss << "  " << i << ") type:" << ConvertShaderAttibuteToString(type) << " name:" << longName.str() << " location:" << location << std::endl;
						}
					}
					else
					{
						int location = glGetUniformLocation(shaderProgramHandle, name);
						ss << "  " << i << ") type:" << ConvertShaderAttibuteToString(type) << " name:" << name << " location:" << location << std::endl;
					}
				}
				return ss.str();
			}

			std::string GLUtils::GetShaderProgramInfo(GLuint shaderProgramHandle)
			{
				std::stringstream ss;
				int params = -1;
				ss << "--------------------" << std::endl;
				ss << "Shader program " << shaderProgramHandle << " info:" << std::endl;
				glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &params);
				ss << "GL_LINK_STATUS = " << params << std::endl;

				glGetProgramiv(shaderProgramHandle, GL_ATTACHED_SHADERS, &params);
				ss << "GL_ATTACHED_SHADERS = " << params << std::endl;

				ss << GetShaderActiveAttributesInfo(shaderProgramHandle);

				ss << GetShaderActiveUniformsInfo(shaderProgramHandle);

				ss << GetShaderProgramInfoLog(shaderProgramHandle);

				return ss.str();
			}

			std::string GLUtils::GetShaderProgramInfoLog(GLuint shaderProgramHandle)
			{
				std::stringstream ss;
				GLint logLen;
				glGetShaderiv(shaderProgramHandle, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* log = new char[logLen];
					GLsizei written;
					glGetShaderInfoLog(shaderProgramHandle, logLen, &written, log);
					ss << "Shader log: " << log << std::endl;
					SAFE_DELETE_ARRAY(log);
				}
				return ss.str();
			}
		}
	}
}