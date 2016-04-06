#include "CubeStaticData.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Primitives
			{
				glm::vec3 cubeVertices[] =
				{
					// Front face
					glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),
					// Back face
					glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
					// Left face
					glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
					// Right face
					glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
					// Top face
					glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
					// Bottom face
					glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),
				};

				glm::vec3 cubeNormals[6] =
				{
					glm::vec3(0.0f, 0.0f, -1.0f),
					glm::vec3(0.0f, 0.0f, 1.0f),
					glm::vec3(1.0f, 0.0f, 0.0f),
					glm::vec3(-1.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, -1.0f, 0.0f),
					glm::vec3(0.0f, 1.0f, 0.0f)
				};

				glm::vec2 cubeTexCoords[] =
				{
					glm::vec2(0.0f, 1.0f),
					glm::vec2(1.0f, 1.0f),
					glm::vec2(1.0f, 0.0f),
					glm::vec2(1.0f, 0.0f),
					glm::vec2(0.0f, 0.0f),
					glm::vec2(0.0f, 1.0f)
				};
			}
		}
	}
}
