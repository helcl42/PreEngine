#ifndef ISHADER_FACTORY
#define ISHADER_FACTORY

#include "Types/AbstractShader.h"
#include "Types/VertexShader.h"
#include "Types/FragmentShader.h"
#include "Types/GeometryShader.h"

using namespace PreEngine::Render::Shaders::Types;

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{			
			class IShaderFactory
			{
			public:
				// from file
				virtual IShader* CreateVertexShader(std::string filePath) const = 0;

				virtual IShader* CreateFragmentShader(std::string filePath) const = 0;

				virtual IShader* CreateGeometryShader(std::string filePath) const = 0;

				virtual IShader* CreateTesselationControlShader(std::string filePath) const = 0;

				virtual IShader* CreateTesselationEvaluationShader(std::string filePath) const = 0;

				virtual IShader* CreateComputeShader(std::string filePath) const = 0;

				// from content
				virtual IShader* CreateVertexShaderFromSource(const char* source) const = 0;

				virtual IShader* CreateFragmentShaderFromSource(const char* source) const = 0;

				virtual IShader* CreateGeometryShaderFromSource(const char* source) const = 0;

				virtual IShader* CreateTesselationControlShaderFromSource(const char* source) const = 0;

				virtual IShader* CreateTesselationEvaluationShaderFromSource(const char* source) const = 0;

				virtual IShader* CreateComputeShaderFromSource(const char* source) const = 0;

			public:
				virtual ~IShaderFactory() {}
			};
		}
	}
}

#endif

