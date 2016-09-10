#ifndef IHEIGHT_MAP_H
#define IHEIGHT_MAP_H

#include "../../Core/Common.h"
#include "../Shaders/ShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			using namespace PreEngine::Render::Shaders;

			class IHeightMap
			{
			public:
				virtual bool IsLoaded() const = 0;

				virtual void SetRenderScale(float renderX, float renderY, float renderZ) = 0;

				virtual void SetRenderScale(float quadSize, float height) = 0;

				virtual unsigned int GetCountOfRows() const = 0;

				virtual unsigned int GetCountOfColumns() const = 0;

				virtual float GetHeightFromRealVector(glm::vec3 position) const = 0;

				virtual void Init() = 0;

				virtual void Update(float deltaTime) = 0;

				virtual void Render() = 0;

				virtual void RenderGrass() = 0;

				virtual void RenderNormals() = 0;

				virtual void ShutDown() = 0;

				virtual glm::mat4 GetScaleMatrix() const = 0;

				virtual IShaderProgram* GetShaderProgram() const = 0;

				virtual void SetShaderProgram(IShaderProgram* program) = 0;

				virtual IShaderProgram* GetGrassShaderProgram() const = 0;

				virtual void SetGrassShaderProgram(IShaderProgram* program) = 0;

				virtual void SetHasGrass(bool has) = 0;

				virtual bool HasGrass() const = 0;

				virtual void SetMinGrassLevel(float minLevel) = 0;

				virtual float GetMinGrassLevel() const = 0;

				virtual void SetMaxGrassLevel(float maxLevel) = 0;

				virtual float GetMaxGrassLevel() const = 0;

			public:
				virtual ~IHeightMap() {}
			};
		}
	}
}

#endif