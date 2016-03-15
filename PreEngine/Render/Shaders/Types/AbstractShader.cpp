#include "AbstractShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				AbstractShader::AbstractShader()
				{
				}

				AbstractShader::AbstractShader(std::string filePath)
					: m_filePath(filePath)
				{
				}

				AbstractShader::~AbstractShader()
				{
					if (m_handle > 0) glDeleteShader(m_handle);
				}

				std::string AbstractShader::GetSourceString(std::string filePath, int depth)
				{
					std::stringstream ss;
					FileReader fileReader;

					if (depth > MAX_INCLUDE_DEPTH) throw new ShaderProgramException("Infinite Recursion ???: " + filePath);

					if (!fileReader.Open(filePath)) throw new ShaderProgramException("Error while openning file: " + filePath);

					while (!fileReader.IsEOF())
					{
						std::string line = fileReader.ReadLine();
						if (line.find("#include") != line.npos && line.find("//") == line.npos)
						{
							std::string dirPath = fileReader.GetDirectoryPath();
							std::string fileName = line.substr(line.find_first_of('\"') + 1, line.find_last_of('\"') - (line.find_first_of('\"') + 1));
							ss << GetSourceString(dirPath + fileName, ++depth);
						}
						else if (line.find("#version") != line.npos && depth > 0) // first line only in the most parent node is used							
						{
							continue;
						}
						else
						{
#ifdef _DEBUG
							m_lineNumber++;
							Logger::GetInstance().Debug() << std::setfill(' ') << std::setw(3) << m_lineNumber << " | " << line;
#endif
							ss << line << std::endl;
						}
					}					

					return std::string(ss.str());
				}

				void AbstractShader::Compile()
				{
					GLint compileResult;
					glCompileShader(m_handle);
					glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compileResult);
					if (compileResult == GL_FALSE)
					{
						Logger::GetInstance().Error() << "Shader File: " << m_filePath;
						Logger::GetInstance().Error() << "Shader log: " << GLUtils::GetShaderProgramInfoLog(m_handle);
						throw new ShaderProgramException("Compilation of shader " + m_filePath + " failed.");
					}
				}

				void AbstractShader::PrepareFromSource(const char* sourceContent)
				{
					this->Create();
					m_shaderCode = std::string(sourceContent);
					m_shaderCodePointer = m_shaderCode.c_str();
					glShaderSource(m_handle, 1, &m_shaderCodePointer, NULL);
					this->Compile();
				}

				void AbstractShader::Prepare()
				{
					this->Create();
#ifdef _DEBUG
					Logger::GetInstance().Debug() << "-------------------------------------------";
					Logger::GetInstance().Debug() << "Shader File: " << m_filePath;
#endif
					m_shaderCode = GetSourceString(m_filePath);
#ifdef _DEBUG
					Logger::GetInstance().Debug() << "-------------------------------------------";
#endif
					m_shaderCodePointer = m_shaderCode.c_str();

					glShaderSource(m_handle, 1, &m_shaderCodePointer, NULL);
					this->Compile();
				}

				void AbstractShader::DeleteShader()
				{
					glDeleteShader(m_handle);
					m_handle = 0;
				}

				GLuint AbstractShader::GetHandle() const
				{
					return m_handle;
				}
			}
		}
	}
}