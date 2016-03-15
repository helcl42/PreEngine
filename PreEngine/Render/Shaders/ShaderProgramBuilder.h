#ifndef SHADER_PROGRAM_BUILDER_H
#define SHADER_PROGRAM_BUILDER_H


#include "../../Core/Caching/GlobalCache.h"

#include "ShaderProgramException.h"
#include "IShaderProgram.h"
#include "ShaderFactory.h"
#include "ShaderProgram.h"
#include "Types/IShader.h"

#include "../../Utils/IO/FileReader.h"
#include "../../Utils/IO/FileWriter.h"
#include "../../Utils/IO/File.h"

#include "IShaderProgramBuilder.h"

// TODO profile performance + add close handler to cleanup memory
#define SHADER_BINARY_CACHING_ENABLED 0

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			using namespace PreEngine::Utils::IO;
			using namespace PreEngine::Core::Caching;
			 
			class ShaderProgramBuilder : public IShaderProgramBuilder
			{
			private:
				struct BinaryDataInfo
				{
					GLubyte* data;
					GLsizei dataLength;
				};

				IShaderFactory* m_shaderFactory;

				std::map<ShaderType, std::string> m_currentlyBuildProgramShaderPaths;

				std::string m_binaryPath;

			public:
				ShaderProgramBuilder();

				virtual ~ShaderProgramBuilder();

			private:
				void ResetState();

				bool LoadShaderBinary(ShaderProgram* program);

				bool LoadShaderBinaryFromFile(ShaderProgram* program);

				bool LoadShaderBinaryFromCache(ShaderProgram* program);

				bool SaveShaderBinary(ShaderProgram* program);

				bool SaveShaderBinaryToChache(BinaryDataInfo dataInfo);

				bool SetProgramBinaryData(ShaderProgram* program, BinaryDataInfo* dataInfo);
				
				void PrepareProgram(ShaderProgram* program);

			public:
				void SetBinaryPath(const std::string& path);

				void AddShader(ShaderType type, const std::string& path);

				IShaderProgram* Build(bool shouldLink = true, bool shouldValidate = true);
			};
		}
	}
}

#endif