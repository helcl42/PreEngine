#ifndef QUAD_H
#define QUAD_H

#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				enum class QuadType
				{
					FULL,
					LEFT,
					RIGHT,
					BOTTOM,
					TOP
				};

				class Quad : public AbstractDrawableObject
				{
				private:
					QuadType m_type;

				public:
					Quad(QuadType type = QuadType::FULL);

					virtual ~Quad();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLE_FAN);

					void RenderBoundingBox();

					void Delete();
				};
			}
		}
	}
}

#endif