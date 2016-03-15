#ifndef ASSIMP_MODEL_H
#define ASSIMP_MODEL_H

#include "../../../Core/Common.h"
#include "../ModelException.h"
#include "../IModel.h"
#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Textures/Texture.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Assimp
			{
				using namespace PreEngine::Render::VertexBufferObjects;
				using namespace PreEngine::Render::Textures;

				class AssimpModel : public IModel
				{
				private:
					friend class AssimpModelFactory;

				private:
					bool m_defaultTexturesEnabled;

					bool m_isLoaded;

					bool m_hasBumpMap;

					bool m_renderWithAdjacents;


					IVertexBufferObject* m_vbo;

					IVertexBufferObject* m_vboBumpMap;

					IVertexBufferObject* m_vboIndices;

					GLuint m_vertexAttributeObject;

					unsigned int m_countOfFaces;

					std::vector<int> m_meshStartIndices;

					std::vector<int> m_meshSizes;


					int m_countOfMaterials;

					ITexture* m_normalTexrure;

					std::vector<ITexture*> m_textures;

					std::vector<int> m_materialIndices;

				public:
					AssimpModel();

					virtual ~AssimpModel();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLES);

					void RenderBoundingBox();

					void Delete();

					bool IsLoaded() const;

					void SetDefaultTexturesEnabled(bool enabled);

					bool IsDefaultTexturesEnabled() const;

					unsigned int GetPolygonCount() const;
				};
			}
		}
	}
}

#endif