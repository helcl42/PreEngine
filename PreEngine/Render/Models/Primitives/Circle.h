#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Circle : public AbstractDrawableObject
				{
				private:
					float m_radius = 1.0f;

					unsigned int m_numberOfSides = 0;

					unsigned int m_numberOfVertices = 0;

				public:
					Circle(float radius, unsigned int numberOfSides);

					virtual ~Circle();

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
