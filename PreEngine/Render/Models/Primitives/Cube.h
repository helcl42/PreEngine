#ifndef CUBE_H
#define CUBE_H

#include "AbstractDrawableObject.h"
#include "CubeStaticData.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Cube : public AbstractDrawableObject
				{
				public:
					Cube();

					virtual ~Cube();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLES);

					void Delete();
				};
			}
		}
	}
}

#endif