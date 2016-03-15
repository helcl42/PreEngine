#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "../../Core/Caching/Cache.h"

#include "ShaderProgramException.h"
#include "IShaderProgram.h"

#include "Types/IShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			using namespace PreEngine::Core::Caching;
			using namespace PreEngine::Utils::GL;

			class ShaderProgramBuilder;

			class ShaderProgram : public IShaderProgram
			{
			public:
				friend ShaderProgramBuilder;

			private:		
				GLuint m_handle;

				Cache<std::string, GLint> m_uniformsCache;

				std::vector<IShader*> m_shaders;

				ShaderProgramStatus m_status;

			public:
				ShaderProgram();

				virtual ~ShaderProgram();

			public:
				GLuint Create();

				void Link(bool validate = true);

				void Validate();

				void Use();

				void AddShader(IShader* shader);

				void Delete();

				void DeleteShaders();

				GLuint GetHandle() const;

				ShaderProgramStatus GetStatus() const;

			public:
				void BindAttribLocation(GLuint location, const std::string& name);

				void BindFragDataLocation(GLuint location, const std::string& name);


				GLuint GetSubroutineLocation(ShaderType shaderType, const std::string& subroutineName);

				void ActivateSubroutine(ShaderType shaderType, const std::string& subroutineName);


				GLint GetUniformLocation(const std::string& name);

				void SetUniform(const std::string& name, float x, float y, float z);

				void SetUniform(const std::string& name, const glm::vec2& v);

				void SetUniform(const std::string& name, const glm::vec3& v);

				void SetUniform(const std::string& name, const glm::vec4& v);

				void SetUniform(const std::string& name, const glm::mat4& m);

				void SetUniform(const std::string& name, const glm::mat3& m);

				void SetUniform(const std::string& name, float val);

				void SetUniform(const std::string& name, int val);

				void SetUniform(const std::string& name, bool val);

				void SetUniform(const std::string& name, GLuint val);
			};
		}
	}
}

#endif