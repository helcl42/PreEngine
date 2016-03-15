#ifndef ABSTRACT_SHADER_H
#define ABSTRACT_SHADER_H

#include "IShader.h"
#include "../ShaderProgramException.h"
#include "../../../Utils/IO/FileReader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			namespace Types
			{
				using namespace PreEngine::Utils::IO;
				using namespace PreEngine::Utils::GL;

				class AbstractShader : public IShader
				{
				protected:
					const int MAX_INCLUDE_DEPTH = 10;

					GLuint m_handle;

					std::string m_filePath;

					std::string m_shaderCode;

					const GLchar* m_shaderCodePointer;
#ifdef _DEBUG
					unsigned int m_lineNumber = 0;
#endif
				public:
					AbstractShader();

					AbstractShader(std::string filePath);

					virtual ~AbstractShader();

				protected:
					virtual GLuint Create() = 0;

					std::string GetSourceString(std::string filePath, int depth = 0);
					
					void Compile();

				public:
					void Prepare();

					void PrepareFromSource(const char* sourceContent);

					void DeleteShader();

					GLuint GetHandle() const;
				};
			}
		}
	}
}

#endif
