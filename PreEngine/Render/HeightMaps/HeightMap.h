#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include "../../Core/Common.h"
#include "../VertexBufferObjects/VertexBufferObject.h"
#include "../Shaders/ShaderProgram.h"
#include "../Shaders/ShaderFactory.h"
#include "IHeightMap.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			using namespace PreEngine::Render::Shaders;
			using namespace PreEngine::Render::VertexBufferObjects;

			class HeightMapFactory;

			class HeightMap : public IHeightMap
			{
			private:
				friend class HeightMapFactory;

			private:
				bool m_isLoaded;

				unsigned int m_rows;

				unsigned int m_cols;

				std::vector<std::vector<glm::vec3> > m_vertexData;

				glm::vec3 m_renderScale;

				GLuint m_vertexAttributeObject;

				IVertexBufferObject* m_vbo;

				IVertexBufferObject* m_vboIndices;

				IVertexBufferObject* m_vboGrass;

				IShaderProgram* m_program;

				IShaderFactory* m_shaderFactory;

				bool m_hasGrass;

				float m_minGrassLevel = 0.0f;

				float m_maxGrassLevel = 1.0f;

				int m_countOfGrassTraingles = 0;

				GLuint m_grassVertexAttributeObject;

				IShaderProgram* m_grassProgram;

				float m_deltaTime = 0.0f;

				float m_elasedTime = 0.0f;

			public:
				HeightMap();

				virtual ~HeightMap();

			private:
				void DeleteGrass();

				void GenerateGrass();

			public:
				bool IsLoaded() const;

				void SetRenderScale(float renderX, float renderY, float renderZ);

				void SetRenderScale(float quadSize, float height);

				unsigned int GetCountOfRows() const;

				unsigned int GetCountOfColumns() const;

				float GetHeightFromRealVector(glm::vec3 position) const;

				void Init();

				void Update(float deltaTime);

				void Render();

				void RenderGrass();

				void RenderNormals();

				void ShutDown();

				glm::mat4 GetScaleMatrix() const;

				IShaderProgram* GetShaderProgram() const;

				void SetShaderProgram(IShaderProgram* program);

				IShaderProgram* GetGrassShaderProgram() const;

				void SetGrassShaderProgram(IShaderProgram* program);

				void SetHasGrass(bool has);

				bool HasGrass() const;

				void SetMinGrassLevel(float minLevel);

				float GetMinGrassLevel() const;

				void SetMaxGrassLevel(float maxLevel);

				float GetMaxGrassLevel() const;
			};
		}
	}
}

#endif