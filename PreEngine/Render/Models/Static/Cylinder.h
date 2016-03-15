#ifndef CYLINDER_H
#define CYLINDER_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				class Cylinder : public AbstractDrawableObject
				{
				private:
					float m_radius;

					float m_height;

					unsigned int m_subDivAround;

					float m_mapU;

					float m_mapV;

				public:
					Cylinder(float radius, float height, unsigned int subDivAround, float mapU, float mapV);

					virtual ~Cylinder();

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