#ifndef TORUS_H
#define TORUS_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				class Torus : public AbstractDrawableObject
				{
				private:
					float m_radius;

					float m_tubeRadius;

					unsigned int m_subDivAround;

					unsigned int m_subDivTube;

					unsigned int m_countOfFaces;

				public:
					Torus(float radius, float tubeRadius, unsigned int subDivAround, unsigned int subDivTube);

					virtual ~Torus();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLES);

					void RenderBoundingBox();

					void Delete();
				};
			}
		}
	}
}

#endif