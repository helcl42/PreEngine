#ifndef QUAD_H
#define QUAD_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Quad : public AbstractDrawableObject
				{
				public:
					Quad();

					virtual ~Quad();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLE_FAN);

					void Delete();
				};
			}
		}
	}
}

#endif