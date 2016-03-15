#ifndef VIEW_FRUSTUM_MESSAGES_H
#define VIEW_FRUSTUM_MESSAGES_H

#include "../../Core/Common.h"
#include "../../Core/Events/BaseEvent.h"

#include "../SceneLayout.h"
#include "../ScenePosition.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Frustums
		{
			namespace Events
			{
				using namespace PreEngine::Core::Events;
				using namespace PreEngine::Render;

				struct OnViewFrustumChange : BaseEvent
				{
					int sceneId;

					int width;

					int height;

					glm::mat4 projectionMatrix;

					glm::mat4 orthoMatrix;

					float fieldOfView;

					float nearClippingPlane; // 0.3f

					float farClippingPlane; // 100.0f


					OnViewFrustumChange() {}

					OnViewFrustumChange(int sceneId, int w, int h, glm::mat4 proj, glm::mat4 ortho, float fov, float nearCP, float farCP)
						: sceneId(sceneId), width(w), height(h), projectionMatrix(proj), orthoMatrix(ortho), fieldOfView(fov), nearClippingPlane(nearCP), farClippingPlane(farCP)
					{
					}

					virtual ~OnViewFrustumChange() {}
				};


				struct OnResize : BaseEvent
				{
					int sceneId;

					int offsetX;

					int offsetY;

					int width;

					int height;


					OnResize() {}

					OnResize(int sceneId, int offsetX, int offsetY, int w, int h)
						: sceneId(sceneId), offsetX(offsetX), offsetY(offsetY), width(w), height(h)
					{
					}

					virtual ~OnResize()
					{
					}
				};

				struct OnViewPortChange : BaseEvent
				{
					int sceneId;

					int offsetX;

					int offsetY;

					int width;

					int height;

					SceneLayout sceneLayout;

					ScenePosition scenePosition;


					OnViewPortChange() {}

					OnViewPortChange(int sceneId, int offsetX, int offsetY, int w, int h, SceneLayout layout, ScenePosition position)
						: sceneId(sceneId), offsetX(offsetX), offsetY(offsetY), width(w), height(h), sceneLayout(layout), scenePosition(position)
					{
					}

					virtual ~OnViewPortChange()
					{
					}
				};
			}
		}
	}
}

#endif