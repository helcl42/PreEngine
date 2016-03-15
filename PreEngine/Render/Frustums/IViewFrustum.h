#ifndef IVIEW_FRUSTUM_H
#define IVIEW_FRUSTUM_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Frustums
		{
			class IViewFrustum
			{
			public:
				virtual glm::mat4 GetOrthographicProjectionMatrix() const = 0;

				virtual glm::mat4 GetPerspectiveProjectionMatrix() const = 0;

				virtual float GetAspectRatio() const = 0;

				virtual float GetFieldOfView() const = 0;

				virtual void SetFieldOfView(float fox) = 0;

				virtual int GetOffsetX() const = 0;

				virtual void SetOffsetX(int offsetX) = 0;

				virtual int GetOffsetY() const = 0;

				virtual void SetOffsetY(int offsetY) = 0;

				virtual int GetWidth() const = 0;

				virtual void SetWidth(int w) = 0;

				virtual int GetHeight() const = 0;

				virtual void SetHeight(int h) = 0;

				virtual float GetNearClippingPlane() const = 0;

				virtual void SetNearClippingPlane(float n) = 0;

				virtual float GetFarClippingPlane() const = 0;

				virtual void SetFarClippingPlane(float f) = 0;

				virtual void ResizeToFull() = 0;

			public:
				virtual ~IViewFrustum() {};
			};
		}
	}
}

#endif