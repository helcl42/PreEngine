#ifndef LINE_H
#define LINE_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				class Line : public AbstractDrawableObject
				{
				private:
					glm::vec3 m_vertexA;

					glm::vec3 m_vertexB;

				private:
					void GerateData();

					void GenerateDataIndices();

				public:
					Line(glm::vec3 vA, glm::vec3 vB);

					virtual ~Line();

				public:
					void Init();

					void Render(GLenum how = GL_LINES);

					void RenderBoundingBox();

					void Delete();
				};
			}
		}
	}
}

#endif