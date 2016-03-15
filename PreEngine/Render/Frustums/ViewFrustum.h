#ifndef VIEW_FRUSTUM_H
#define VIEW_FRUSTUM_H

#include "../../Core/Common.h"
#include "../../Core/Events/EventHandler.h"
#include "../../Windows/WindowEvents.h"
#include "../../Inputs/Core/Mouses/MouseEvents.h"
#include "../../Utils/Render/RenderUtil.h"

#include "ViewFrustumEvents.h"
#include "IViewFrustum.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Frustums
		{
			using namespace PreEngine;
			using namespace PreEngine::Core;
			using namespace PreEngine::Core::Events;	
			using namespace PreEngine::Render;
			using namespace PreEngine::Inputs::Core;

			using namespace PreEngine::Utils::Render;

			class ViewFrustum : public IViewFrustum
			{
			private:
				unsigned int m_sceneId;

				int m_width;

				int m_height;				

				int m_offsetX;

				int m_offsetY;

				glm::mat4 m_perspectiveProjectionMatrix;

				glm::mat4 m_orthographicProjectionMatrix;

				float m_fieldOfView;

				float m_nearClippingPlane;

				float m_farClippingPlane;

				EventHandler<ViewFrustum, Frustums::Events::OnResize>* m_resizeToHandler;

				EventHandler<ViewFrustum, Windows::Events::OnCreate>* m_onCreateHandler;

				EventHandler<ViewFrustum, Windows::Events::OnClose>* m_onCloseHandler;

				EventHandler<ViewFrustum, Windows::Events::OnResize>* m_onResizeHandler;

				EventHandler<ViewFrustum, Frustums::Events::OnViewPortChange>* m_onViewPortChangeHandler;

				EventHandler<ViewFrustum, Mouses::Events::OnMouseScroll>* m_onScrollHandler;

			private:
				void UpdateMatrices();

			public:
				ViewFrustum(unsigned int sceneId);

				ViewFrustum(unsigned int sceneId, int w, int h, float fov, float nearClippingPlane, float farClippingPlane);

				virtual ~ViewFrustum();

			public:
				void operator() (const Frustums::Events::OnResize& resize);

				void operator() (const Windows::Events::OnCreate& create);

				void operator() (const Windows::Events::OnClose& close);

				void operator() (const Windows::Events::OnResize& resize);

				void operator() (const Frustums::Events::OnViewPortChange& resize);

				void operator() (const Mouses::Events::OnMouseScroll& scroll);

			public:
				glm::mat4 GetOrthographicProjectionMatrix() const;

				glm::mat4 GetPerspectiveProjectionMatrix() const;

				float GetAspectRatio() const;

				float GetFieldOfView() const;

				void SetFieldOfView(float fox);

				int GetWidth() const;

				void SetWidth(int w);

				int GetHeight() const;

				void SetHeight(int h);

				int GetOffsetX() const;

				void SetOffsetX(int offsetX);

				int GetOffsetY() const;

				void SetOffsetY(int offsetY);

				float GetNearClippingPlane() const;

				void SetNearClippingPlane(float n);

				float GetFarClippingPlane() const;

				void SetFarClippingPlane(float f);

				void Resize(int offsetX, int offsetY, int width, int height);

				void ResizeToFull();
			};
		}
	}
}

#endif