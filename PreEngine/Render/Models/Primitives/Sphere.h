#ifndef SPHERE_H
#define SPHERE_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Sphere : public AbstractDrawableObject
				{
				private:
					float m_radius;

					int m_subDivY;

					int m_subDivZ;

					int m_countOfFaces;

				public:
					Sphere(float radius, int subDivY, int subDivZ);

					virtual ~Sphere();

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