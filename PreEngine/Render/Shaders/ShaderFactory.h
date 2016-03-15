#ifndef SHADER_FACTORY
#define SHADER_FACTORY

#include "IShaderFactory.h"
#include "Types/ComputeShader.h"
#include "Types/FragmentShader.h"
#include "Types/GeometryShader.h"
#include "Types/TesselationControlShader.h"
#include "Types/TesselationEvaluationShader.h"
#include "Types/VertexShader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			class ShaderFactory : public IShaderFactory
			{
			public:
				ShaderFactory();

				virtual ~ShaderFactory();

			public:
				IShader* CreateVertexShader(std::string filePath) const;

				IShader* CreateFragmentShader(std::string filePath) const;

				IShader* CreateGeometryShader(std::string filePath) const;

				IShader* CreateTesselationControlShader(std::string filePath) const;

				IShader* CreateTesselationEvaluationShader(std::string filePath) const;

				IShader* CreateComputeShader(std::string filePath) const;

				
				IShader* CreateVertexShaderFromSource(const char* source) const;

				IShader* CreateFragmentShaderFromSource(const char* source) const;

				IShader* CreateGeometryShaderFromSource(const char* source) const;

				IShader* CreateTesselationControlShaderFromSource(const char* source) const;

				IShader* CreateTesselationEvaluationShaderFromSource(const char* source) const;

				IShader* CreateComputeShaderFromSource(const char* source) const;
			};
		}
	}
}

#endif