#ifndef OBJ_MODEL_H
#define OBJ_MODEL_H

#include "../IModel.h"
#include "../ModelException.h"
#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Textures/Texture.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace ObjModels
			{
				using namespace PreEngine::Render::VertexBufferObjects;
				using namespace PreEngine::Render::Textures;
				using namespace PreEngine::Utils;

				class ObjModel : public IModel
				{
				private:
					friend class ObjModelFactory;

				private:
					bool m_isLoaded;

					bool m_defaultTexturesEnabled;

					int m_attrBitField;

					unsigned int m_countOfFaces;

					GLuint m_vertexAttributeObject;

					GLuint m_vertexAttributeObjectBB;

					IVertexBufferObject* m_vbo;

					IVertexBufferObject* m_vboBB;

					IVertexBufferObject* m_vboBBIndices;

					ITexture* m_ambientTexture;

				public:
					ObjModel();

					virtual ~ObjModel();

				public:
					void SetDefaultTexturesEnabled(bool enabled);

					bool IsDefaultTexturesEnabled() const;
					
					void Init();

					void Render(GLenum how = GL_TRIANGLES);

					void RenderBoundingBox();

					void Delete();

					bool IsLoaded() const;

					unsigned int GetPolygonCount() const;
				};
			}
		}
	}
}

#endif