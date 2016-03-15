#ifndef ISHADER_PROGRAM_BUILDER_H
#define ISHADER_PROGRAM_BUILDER_H

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			class IShaderProgramBuilder
			{
			public:
				virtual void SetBinaryPath(const std::string& path) = 0;

				virtual void AddShader(ShaderType type, const std::string& path) = 0;

				virtual IShaderProgram* Build(bool shouldLink = true, bool shouldValidate = true) = 0;

			public:
				virtual ~IShaderProgramBuilder() {}
			};
		}
	}
}

#endif