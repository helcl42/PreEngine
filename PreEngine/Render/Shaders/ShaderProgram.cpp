#include "ShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			ShaderProgram::ShaderProgram()
				: m_handle(0), m_status(ShaderProgramStatus::NOT_CREATED)
			{
			}

			ShaderProgram::~ShaderProgram()
			{
				for (size_t i = 0; i < m_shaders.size(); i++)
				{
					SAFE_DELETE(m_shaders[i]);
				}
			}

			GLuint ShaderProgram::Create()
			{
				if (m_status >= ShaderProgramStatus::CREATED) throw ShaderProgramException("Program is already created.");

				m_handle = glCreateProgram();
				if (m_handle == GL_FALSE)
				{
					m_status = ShaderProgramStatus::NOT_CREATED;
					throw ShaderProgramException("Error creating program object.");
				}
				m_status = ShaderProgramStatus::CREATED;
				return m_handle;
			}

			void ShaderProgram::Link(bool validate)
			{
				if (m_status < ShaderProgramStatus::CREATED) throw ShaderProgramException("Could not attach shader to NOT_CREATED program");

				GLint status;
				glProgramParameteri(m_handle, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
				glLinkProgram(m_handle);
				glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
				if (status == GL_FALSE)
				{
					Logger::GetInstance().Error() << "Program log: " << GLUtils::GetShaderProgramInfoLog(m_handle);
					throw ShaderProgramException("Failed to link shader program!");
				}
				m_status = ShaderProgramStatus::LINKED;

				if (validate) Validate();
			}

			void ShaderProgram::Validate()
			{
				if (m_status < ShaderProgramStatus::LINKED) throw ShaderProgramException("Program is not linked");
#ifdef _DEBUG
				GLint status;
				glValidateProgram(m_handle);
				glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &status);

				if (GL_FALSE == status)
				{
					Logger::GetInstance().Error() << "Program log: " << GLUtils::GetShaderProgramInfoLog(m_handle);
					throw ShaderProgramException("Program failed to validate");
				}
#endif
				m_status = ShaderProgramStatus::VALIDATED;
			}

			void ShaderProgram::Use()
			{
				if (m_handle <= 0 || (m_status < LINKED)) throw ShaderProgramException("Shader has not been linked");
				glUseProgram(m_handle);
				m_status = ShaderProgramStatus::IN_USE;
			}

			void ShaderProgram::AddShader(IShader* shader)
			{
				m_shaders.push_back(shader);
				if (m_status < ShaderProgramStatus::CREATED) throw ShaderProgramException("Could not attach shader to NOT_CREATED program");
				glAttachShader(m_handle, shader->GetHandle());
			}

			void ShaderProgram::DeleteShaders()
			{
				for (std::vector<IShader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
				{
					(*it)->DeleteShader();
				}
			}

			void ShaderProgram::Delete()
			{
				glDeleteProgram(m_handle);
				m_handle = 0;
				m_status = ShaderProgramStatus::NOT_CREATED;
			}

			GLuint ShaderProgram::GetHandle() const
			{
				return m_handle;
			}

			ShaderProgramStatus ShaderProgram::GetStatus() const
			{
				return m_status;
			}

			void ShaderProgram::BindAttribLocation(GLuint location, const std::string& name)
			{
				glBindAttribLocation(m_handle, location, name.c_str());
			}

			void ShaderProgram::BindFragDataLocation(GLuint location, const std::string& name)
			{
				glBindFragDataLocation(m_handle, location, name.c_str());
			}

			GLuint ShaderProgram::GetSubroutineLocation(ShaderType shaderType, const std::string& subroutineName)
			{
				GLuint location = glGetSubroutineIndex(m_handle, shaderType, subroutineName.c_str());
				if (location == GL_INVALID_INDEX) throw ShaderProgramException("Uniform subroutine with name " + subroutineName + " does not exist.");
				return location;
			}

			void ShaderProgram::ActivateSubroutine(ShaderType shaderType, const std::string& subroutineName)
			{
				GLuint location = GetSubroutineLocation(shaderType, subroutineName);
				glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &location);
			}

			GLint ShaderProgram::GetUniformLocation(const std::string& uniformName)
			{
				if (!m_uniformsCache.Contains(uniformName))
				{
					GLint location = glGetUniformLocation(m_handle, uniformName.c_str());
					if (location < 0) throw ShaderProgramException("Uniform var with name " + uniformName + " does not exist.");
					m_uniformsCache.Add(uniformName, location);
					return location;
				}
				else
				{
					return m_uniformsCache.Get(uniformName);
				}
			}

			void ShaderProgram::SetUniform(const std::string& name, float x, float y, float z)
			{
				GLint location = GetUniformLocation(name);
				glUniform3f(location, x, y, z);
			}

			void ShaderProgram::SetUniform(const std::string& name, const glm::vec2& v)
			{
				GLint location = GetUniformLocation(name);
				glUniform2f(location, v.x, v.y);
			}

			void ShaderProgram::SetUniform(const std::string& name, const glm::vec3& v)
			{
				GLint location = GetUniformLocation(name);
				glUniform3f(location, v.x, v.y, v.z);
			}

			void ShaderProgram::SetUniform(const std::string& name, const glm::vec4& v)
			{
				GLint location = GetUniformLocation(name);
				glUniform4f(location, v.x, v.y, v.z, v.w);
			}

			void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& m)
			{
				GLint location = GetUniformLocation(name);
				glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
			}

			void ShaderProgram::SetUniform(const std::string& name, const glm::mat3& m)
			{
				GLint location = GetUniformLocation(name);
				glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
			}

			void ShaderProgram::SetUniform(const std::string& name, float val)
			{
				GLint location = GetUniformLocation(name);
				glUniform1f(location, val);
			}

			void ShaderProgram::SetUniform(const std::string& name, int val)
			{
				GLint location = GetUniformLocation(name);
				glUniform1i(location, val);
			}

			void ShaderProgram::SetUniform(const std::string& name, bool val)
			{
				GLint location = GetUniformLocation(name);
				glUniform1i(location, val);
			}

			void ShaderProgram::SetUniform(const std::string& name, GLuint val)
			{
				GLint location = GetUniformLocation(name);
				glUniform1ui(location, val);
			}
		}
	}
}