#ifndef ABSTRACT_DRAWABLE_OBJECT_H
#define ABSTRACT_DRAWABLE_OBJECT_H

#include "../../VertexBufferObjects/VertexBufferObject.h"

#include "../IModel.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				using namespace PreEngine::Render::VertexBufferObjects;

				class AbstractDrawableObject : public IModel
				{
				protected:
					GLuint m_vertexArrayObject;

					IVertexBufferObject* m_vbo;

					bool m_isLoaded = false;

					bool m_defaultTexturesEnabled = true;

					unsigned int m_countOfFaces;

				protected:
					AbstractDrawableObject();

					virtual ~AbstractDrawableObject();

				protected:
					void Prepare();

					void Upload();

				public:
					void SetDefaultTexturesEnabled(bool enabled);

					bool IsDefaultTexturesEnabled() const;

					bool IsLoaded() const;

					unsigned int GetPolygonCount() const;

					virtual void RenderBoundingBox();
				};
			}
		}
	}
}

#endif