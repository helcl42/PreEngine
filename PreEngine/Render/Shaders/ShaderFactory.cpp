#include "ShaderFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Shaders
		{
			ShaderFactory::ShaderFactory()
			{
			}

			ShaderFactory::~ShaderFactory()
			{
			}

			IShader* ShaderFactory::CreateVertexShader(std::string filePath) const
			{
				IShader* newShader = new VertexShader(filePath);
				newShader->Prepare();
				return newShader;
			}

			IShader* ShaderFactory::CreateFragmentShader(std::string filePath) const
			{
				IShader* newShader = new FragmentShader(filePath);
				newShader->Prepare();
				return newShader;
			}

			IShader* ShaderFactory::CreateGeometryShader(std::string filePath) const
			{
				IShader* newShader = new GeometryShader(filePath);
				newShader->Prepare();
				return newShader;
			}

			IShader* ShaderFactory::CreateTesselationControlShader(std::string filePath) const
			{
				IShader* newShader = new TesselationControlShader(filePath);
				newShader->Prepare();
				return newShader;
			}

			IShader* ShaderFactory::CreateTesselationEvaluationShader(std::string filePath) const
			{
				IShader* newShader = new TesselationEvaluationShader(filePath);
				newShader->Prepare();
				return newShader;
			}

			IShader* ShaderFactory::CreateComputeShader(std::string filePath) const
			{
				IShader* newShader = new ComputeShader(filePath);
				newShader->Prepare();
				return newShader;
			}


			IShader* ShaderFactory::CreateVertexShaderFromSource(const char* source) const
			{
				IShader* newShader = new VertexShader();
				newShader->PrepareFromSource(source);
				return newShader;
			}

			IShader* ShaderFactory::CreateFragmentShaderFromSource(const char* source) const
			{
				IShader* newShader = new FragmentShader();
				newShader->PrepareFromSource(source);
				return newShader;
			}

			IShader* ShaderFactory::CreateGeometryShaderFromSource(const char* source) const
			{
				IShader* newShader = new GeometryShader();
				newShader->PrepareFromSource(source);
				return newShader;
			}

			IShader* ShaderFactory::CreateTesselationControlShaderFromSource(const char* source) const
			{
				IShader* newShader = new TesselationControlShader();
				newShader->PrepareFromSource(source);
				return newShader;
			}

			IShader* ShaderFactory::CreateTesselationEvaluationShaderFromSource(const char* source) const
			{
				IShader* newShader = new TesselationEvaluationShader();
				newShader->PrepareFromSource(source);
				return newShader;
			}

			IShader* ShaderFactory::CreateComputeShaderFromSource(const char* shaderContent) const
			{
				IShader* newShader = new ComputeShader();
				newShader->PrepareFromSource(shaderContent);
				return newShader;
			}
		}
	}
}