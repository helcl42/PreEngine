#ifndef RAY_H
#define RAY_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			struct Ray
			{
				glm::vec3 vertexA;
				glm::vec3 vertexB;


				Ray();

				Ray(glm::vec3 a, glm::vec3 b);

				virtual ~Ray();


				glm::vec3 GetDirection() const;

				float GetLength() const;
			};
		}
	}
}

#endif