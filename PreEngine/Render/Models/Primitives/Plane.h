#ifndef PLANE_H
#define PLANE_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Plane : public AbstractDrawableObject
				{
				private:
					float m_xSize;

					float m_zSize;

					unsigned int m_xDivs;

					unsigned int m_zDivs;

					float m_sMax;

					float m_tMax;

					IVertexBufferObject* m_vboIndices;

				private:
					void GerateData();

					void GenerateDataIndices();

				public:
					Plane(float xsize, float zsize, unsigned int xdivs, unsigned int zdivs, float smax = 1.0f, float tmax = 1.0f);

					virtual ~Plane();

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