#ifndef IOBJ_MODEL_H
#define IOBJ_MODEL_H

#include "../../../Core/Common.h"
#include "ModelException.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			class IModel
			{
			public:
				virtual void Init() = 0;

				virtual void Update(float deltaTime) {};

				virtual void Render(GLenum how = GL_TRIANGLES) = 0;

				virtual void RenderBoundingBox() = 0;

				virtual void Delete() = 0;

				virtual bool IsLoaded() const = 0;

				virtual unsigned int GetPolygonCount() const = 0;

				virtual bool IsDefaultTexturesEnabled() const = 0;

				virtual void SetDefaultTexturesEnabled(bool enabled) = 0;

			public:
				virtual ~IModel() {}
			};
		}
	}
}

#endif