#ifndef ISHADER_PROGRAM_H
#define ISHADER_PROGRAM_H

#include "ShaderProgramStatus.h"
#include "Types/IShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			using namespace PreEngine::Render::Shaders::Types;

			class IShaderProgram
			{
			public:
				virtual GLuint Create() = 0;

				virtual void Link(bool validate = true) = 0;

				virtual void Validate() = 0;

				virtual void Use() = 0;

				virtual void AddShader(IShader* shader) = 0;

				virtual GLuint GetHandle() const = 0;

				virtual void Delete() = 0;

				virtual void DeleteShaders() = 0;

				virtual ShaderProgramStatus GetStatus() const = 0;


				virtual void BindAttribLocation(GLuint location, const std::string& name) = 0;

				virtual void BindFragDataLocation(GLuint location, const std::string& name) = 0;


				virtual GLuint GetSubroutineLocation(ShaderType shaderType, const std::string& subroutineName) = 0;

				virtual void ActivateSubroutine(ShaderType shaderType, const std::string& subroutineName) = 0;


				virtual GLint GetUniformLocation(const std::string& name) = 0;

				virtual void SetUniform(const std::string& name, float x, float y, float z) = 0;

				virtual void SetUniform(const std::string& name, const glm::vec2& v) = 0;

				virtual void SetUniform(const std::string& name, const glm::vec3& v) = 0;

				virtual void SetUniform(const std::string& name, const glm::vec4& v) = 0;

				virtual void SetUniform(const std::string& name, const glm::mat4& m) = 0;

				virtual void SetUniform(const std::string& name, const glm::mat3& m) = 0;

				virtual void SetUniform(const std::string& name, float val) = 0;

				virtual void SetUniform(const std::string& name, int val) = 0;

				virtual void SetUniform(const std::string& name, bool val) = 0;

				virtual void SetUniform(const std::string& name, GLuint val) = 0;

			public:
				virtual ~IShaderProgram() {}
			};
		}
	}
}

#endif