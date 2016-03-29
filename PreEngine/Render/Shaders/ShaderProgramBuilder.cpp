#include "ShaderProgramBuilder.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			void ShaderProgramBuilder::ResetState()
			{
				m_binaryPath = "";
				m_currentlyBuildProgramShaderPaths.clear();
			}

			ShaderProgramBuilder::ShaderProgramBuilder()
			{
				m_shaderFactory = new ShaderFactory();
				ResetState();
			}

			ShaderProgramBuilder::~ShaderProgramBuilder()
			{
				SAFE_DELETE(m_shaderFactory);
			}

			void ShaderProgramBuilder::PrepareProgram(ShaderProgram* program)
			{
				for (std::map<ShaderType, std::string>::const_iterator ci = m_currentlyBuildProgramShaderPaths.begin(); ci != m_currentlyBuildProgramShaderPaths.end(); ++ci)
				{
					IShader* shader = NULL;
					if (ci->first == ShaderType::VERTEX_SHADER) shader = m_shaderFactory->CreateVertexShader(ci->second);
					else if (ci->first == ShaderType::TESSELATION_CONTROL_SHADER) shader = m_shaderFactory->CreateTesselationControlShader(ci->second);
					else if (ci->first == ShaderType::TESSELATION_EVALUATION_SHADER) shader = m_shaderFactory->CreateTesselationEvaluationShader(ci->second);
					else if (ci->first == ShaderType::GEOMETRY_SHADER) shader = m_shaderFactory->CreateGeometryShader(ci->second);
					else if (ci->first == ShaderType::FRAGMENT_SHADER) shader = m_shaderFactory->CreateFragmentShader(ci->second);
					else if (ci->first == ShaderType::COMPUTE_SHADER) shader = m_shaderFactory->CreateComputeShader(ci->second);
					else throw ShaderProgramException("Invalid shader type ?!");
					program->AddShader(shader);
				}
			}

			bool ShaderProgramBuilder::SetProgramBinaryData(ShaderProgram* program, BinaryDataInfo* dataInfo)
			{
				GLint countOfFormats = 0;
				glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &countOfFormats);
				GLint *binaryFormats = new GLint[countOfFormats];
				glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, binaryFormats);

				glProgramParameteri(program->GetHandle(), GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
				glProgramBinary(program->GetHandle(), (GLenum)binaryFormats[0], dataInfo->data, dataInfo->dataLength);

				SAFE_DELETE_ARRAY(binaryFormats);

				GLint status;
				glGetProgramiv(program->GetHandle(), GL_LINK_STATUS, &status);
				if (status != GL_FALSE)
				{
					program->m_status = ShaderProgramStatus::LINKED;
					return true;
				}
				return false;
			}

			bool ShaderProgramBuilder::LoadShaderBinaryFromFile(ShaderProgram* program)
			{
				bool loadSuccess = true;
				FileReader fileReader;
				if (fileReader.Open(m_binaryPath, std::ios::binary))
				{
					GLsizei len = static_cast<GLsizei>(fileReader.GetFileLength());
					GLubyte* binary = new GLubyte[len];
					fileReader.ReadBytes(binary, len);

					BinaryDataInfo dataInfo{ binary, len };
					if (SetProgramBinaryData(program, &dataInfo))
					{
#if SHADER_BINARY_CACHING_ENABLED
						SaveShaderBinaryToChache(dataInfo);
#else
						SAFE_DELETE_ARRAY(binary);
#endif
					}
					else
					{
						SAFE_DELETE_ARRAY(binary);
						loadSuccess = false;
					}
				}
				else
				{
					Logger::GetInstance().Warning() << "Could not open binary shader input file: " + m_binaryPath;
					loadSuccess = false;
				}
				return loadSuccess;
			}

			bool ShaderProgramBuilder::LoadShaderBinary(ShaderProgram* program)
			{
				bool loadSuccess = false;
#if SHADER_BINARY_CACHING_ENABLED
				loadSuccess = LoadShaderBinaryFromCache(program);
#endif
				if (!loadSuccess)
				{
					loadSuccess = LoadShaderBinaryFromFile(program);
				}
				return loadSuccess;
			}

			bool ShaderProgramBuilder::LoadShaderBinaryFromCache(ShaderProgram* program)
			{
				BinaryDataInfo dataInfo = GlobalCache<std::string, BinaryDataInfo>::GetInstance().Get(m_binaryPath);
				if (!SetProgramBinaryData(program, &dataInfo))
				{
					Logger::GetInstance().Info() << "Could not load binary shader from cache key: " + m_binaryPath;
					return false;
				}
				return true;
			}

			bool ShaderProgramBuilder::SaveShaderBinaryToChache(BinaryDataInfo dataInfo)
			{
				if (!GlobalCache<std::string, BinaryDataInfo>::GetInstance().Contains(m_binaryPath))
				{
					GlobalCache<std::string, BinaryDataInfo>::GetInstance().Add(m_binaryPath, dataInfo);
					return true;
				}
				return false;
			}

			bool ShaderProgramBuilder::SaveShaderBinary(ShaderProgram* program)
			{
				GLint countOfBinaryFormats = 0;
				glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &countOfBinaryFormats);
				if (countOfBinaryFormats <= 0) return false;

				bool saveSuccess = true;
				GLint* binaryFormats = new GLint[countOfBinaryFormats];
				glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, binaryFormats);

				GLint binaryLength = 0;
				glGetProgramiv(program->GetHandle(), GL_PROGRAM_BINARY_LENGTH, &binaryLength);

				GLubyte* binaryCode = new GLubyte[binaryLength];
				glGetProgramBinary(program->GetHandle(), binaryLength, NULL, (GLenum*)binaryFormats, binaryCode);

				File::CreateDirectoryByPath(File::GetDirectoryPath(m_binaryPath));

				FileWriter fileWriter;
				if (fileWriter.Open(m_binaryPath, std::ios::binary))
				{
					fileWriter.WriteBytes(binaryCode, binaryLength);
#if SHADER_BINARY_CACHING_ENABLED
					SaveShaderBinaryToChache(BinaryDataInfo{ binaryCode, binaryLength });					
#endif
				}
				else
				{
					Logger::GetInstance().Error() << "Could not open " + m_binaryPath + "!";
					saveSuccess = false;
				}

				SAFE_DELETE_ARRAY(binaryCode);
				SAFE_DELETE_ARRAY(binaryFormats);

				return saveSuccess;
			}

			void ShaderProgramBuilder::SetBinaryPath(const std::string& path)
			{
				m_binaryPath = path;
			}

			void ShaderProgramBuilder::AddShader(ShaderType type, const std::string& path)
			{
				m_currentlyBuildProgramShaderPaths.insert(std::make_pair(type, path));
			}

			IShaderProgram* ShaderProgramBuilder::Build(bool shouldLink, bool shouldValidate)
			{
				ShaderProgram* program = new ShaderProgram();
				program->Create();

				if (!m_binaryPath.empty())
				{
					if (!LoadShaderBinary(program))
					{
						PrepareProgram(program);
						if (shouldLink)
						{
							program->Link(false);
							if (!SaveShaderBinary(program)) throw ShaderProgramException("Binary file " + m_binaryPath + " was not saved!");
						}
					}
				}
				else
				{
					PrepareProgram(program);
					if (shouldLink) program->Link(false);
				}

				if (shouldValidate) program->Validate();
				Logger::GetInstance().Info() << "Loaded shader: " + m_binaryPath;
				ResetState();
				return program;
			}
		}
	}
}