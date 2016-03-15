#include "Ray.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			Ray::Ray()
			{
			}

			Ray::Ray(glm::vec3 a, glm::vec3 b)
				: vertexA(a), vertexB(b)
			{
			}

			Ray::~Ray()
			{
			}

			glm::vec3 Ray::GetDirection() const
			{
				return glm::normalize(vertexB - vertexA);
			}

			float Ray::GetLength() const
			{
				return glm::distance(vertexA, vertexB);
			}
		}
	}
}