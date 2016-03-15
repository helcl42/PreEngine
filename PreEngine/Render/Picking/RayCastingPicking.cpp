#include "RayCastingPicking.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			RayCastingPicking::RayCastingPicking()
				: m_mousePosition(glm::vec2(0.0f, 0.0f))
			{
				m_mouseMoveHandler = new EventHandler<RayCastingPicking, OnMouseMove>(this);
				m_viewFrustumChangeHandler = new EventHandler<RayCastingPicking, OnViewFrustumChange>(this);
			}

			RayCastingPicking::~RayCastingPicking()
			{
				SAFE_DELETE(m_viewFrustumChangeHandler);
				SAFE_DELETE(m_mouseMoveHandler);
			}

			Ray RayCastingPicking::Get3DRayAtMousePosition(glm::mat4 lookAt)
			{
				glm::vec4 viewPort = glm::vec4(0.0f, 0.0f, m_width, m_height);

				Ray ray;
				ray.vertexA = glm::unProject(glm::vec3(m_mousePosition.x, m_mousePosition.y, 0.0f), lookAt, m_perspectiveProjectionMatrix, viewPort);
				ray.vertexB = glm::unProject(glm::vec3(m_mousePosition.x, m_mousePosition.y, 1.0f), lookAt, m_perspectiveProjectionMatrix, viewPort);
				return ray;
			}

			bool RayCastingPicking::RaySphereCollision(const Ray& ray, glm::vec3 sphereCenter, float sphereRadius)
			{
				glm::vec3 directionToSphere = sphereCenter - ray.vertexA;
				glm::vec3 lineDirection = ray.GetDirection();

				float lineLenght = ray.GetLength();
				float t = glm::dot(directionToSphere, lineDirection);

				glm::vec3 closestPoint;
				if (t < 0.0f) closestPoint = ray.vertexA;
				else if (t >= lineLenght) closestPoint = ray.vertexB;
				else closestPoint = ray.vertexA + lineDirection * t;

				return glm::distance(sphereCenter, closestPoint) <= sphereRadius;
			}

			void RayCastingPicking::operator()(const OnMouseMove& move)
			{
				m_mousePosition = move.actualPosition;
			}

			void RayCastingPicking::operator()(const OnViewFrustumChange& frustum)
			{
				m_width = frustum.width;
				m_height = frustum.height;
				m_perspectiveProjectionMatrix = frustum.projectionMatrix;
				m_orthographicProjectionMatrix = frustum.orthoMatrix;
			}
		}
	}
}