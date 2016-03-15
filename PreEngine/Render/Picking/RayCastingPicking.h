#ifndef RAY_CASTING_PICKING_H
#define RAY_CASTING_PICKING_H

#include "../../Core/Common.h"
#include "../../Core/Events/EventHandler.h"
#include "../../Inputs/Core/Mouses/MouseEvents.h"
#include "../../Render/SceneNode.h"

#include "Ray.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Picking
		{
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;

			using namespace PreEngine::Render::Frustums::Events;
			using namespace PreEngine::Inputs::Core::Mouses::Events;

			class RayCastingPicking
			{
			private:
				glm::vec2 m_mousePosition;

				EventHandler<RayCastingPicking, OnMouseMove>* m_mouseMoveHandler;

				EventHandler<RayCastingPicking, OnViewFrustumChange>* m_viewFrustumChangeHandler;

				unsigned int m_width;

				unsigned int m_height;

				glm::mat4 m_perspectiveProjectionMatrix;

				glm::mat4 m_orthographicProjectionMatrix;

			public:
				RayCastingPicking();

				virtual ~RayCastingPicking();

			public:
				Ray Get3DRayAtMousePosition(glm::mat4 lookAt);

				bool RaySphereCollision(const Ray& ray, glm::vec3 sphereCenter, float sphereRadius);

			public:
				void operator()(const OnMouseMove& move);

				void operator()(const OnViewFrustumChange& frustum);
			};
		}
	}
}

#endif