#include "ViewFrustum.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Frustums
		{
			ViewFrustum::ViewFrustum(unsigned int sceneId)
				: ViewFrustum(sceneId, 1200, 750, 66.0f, 0.1f, 1000.0f)
			{
			}

			ViewFrustum::ViewFrustum(unsigned int sceneId, int w, int h, float fov, float nearClippingPlane, float farClippingPlane)
				: m_sceneId(sceneId), m_offsetX(0), m_offsetY(0), m_width(w), m_height(h), m_fieldOfView(fov), m_nearClippingPlane(nearClippingPlane), m_farClippingPlane(farClippingPlane)
			{
				m_resizeToHandler = new EventHandler<ViewFrustum, Frustums::Events::OnResize>(this);
				m_onCreateHandler = new EventHandler<ViewFrustum, Windows::Events::OnCreate>(this);
				m_onCloseHandler = new EventHandler<ViewFrustum, Windows::Events::OnClose>(this);
				m_onResizeHandler = new EventHandler<ViewFrustum, Windows::Events::OnResize>(this);
				m_onViewPortChangeHandler = new EventHandler<ViewFrustum, Frustums::Events::OnViewPortChange>(this);
				m_onScrollHandler = new EventHandler<ViewFrustum, Mouses::Events::OnMouseScroll>(this);
			}

			ViewFrustum::~ViewFrustum()
			{
				SAFE_DELETE(m_onScrollHandler);
				SAFE_DELETE(m_onViewPortChangeHandler);
				SAFE_DELETE(m_resizeToHandler);
				SAFE_DELETE(m_onResizeHandler);
				SAFE_DELETE(m_onCloseHandler);
				SAFE_DELETE(m_onCreateHandler);
			}

			void ViewFrustum::UpdateMatrices()
			{
				m_perspectiveProjectionMatrix = RenderUtil::GetPerspectiveProjectionMatrix(m_width, m_height, m_fieldOfView, m_nearClippingPlane, m_farClippingPlane);
				m_orthographicProjectionMatrix = RenderUtil::GetOrthographicProjectionMatrix(0, 0, m_width, m_height);

				EventChannel::Broadcast(Frustums::Events::OnViewFrustumChange{ (int)m_sceneId, m_width, m_height, m_perspectiveProjectionMatrix, m_orthographicProjectionMatrix, m_fieldOfView, m_nearClippingPlane, m_farClippingPlane });
			}

			void ViewFrustum::operator() (const Windows::Events::OnCreate& create)
			{
			}

			void ViewFrustum::operator() (const Windows::Events::OnClose& close)
			{
			}

			void ViewFrustum::operator() (const Windows::Events::OnResize& resize)
			{
				if (resize.sceneId == m_sceneId || resize.sceneId == -1)
				{
					Resize(0, 0, resize.width, resize.height);
				}
			}

			void ViewFrustum::operator() (const Frustums::Events::OnResize& resize)
			{
				if (resize.sceneId == m_sceneId || resize.sceneId == -1)
				{
					Resize(resize.offsetX, resize.offsetY, resize.width, resize.height);
				}
			}

			void ViewFrustum::operator() (const Frustums::Events::OnViewPortChange& resize)
			{
				if (resize.sceneId == m_sceneId || resize.sceneId == -1)
				{
					Resize(resize.offsetX, resize.offsetY, resize.width, resize.height);
				}
			}

			void ViewFrustum::operator() (const Mouses::Events::OnMouseScroll& scroll)
			{
				const float ZOOM_SENSITIVITY = -0.2f;
				float fieldOfView = m_fieldOfView + ZOOM_SENSITIVITY * (float)scroll.diff.y;
				if (fieldOfView < 5.0f) fieldOfView = 5.0f;
				if (fieldOfView > 130.0f) fieldOfView = 130.0f;
				m_fieldOfView = fieldOfView;

				UpdateMatrices();
			}

			float ViewFrustum::GetAspectRatio() const
			{
				return RenderUtil::GetAspectRatio(m_width, m_height);
			}

			glm::mat4 ViewFrustum::GetOrthographicProjectionMatrix() const
			{
				return m_orthographicProjectionMatrix;
			}

			glm::mat4 ViewFrustum::GetPerspectiveProjectionMatrix() const
			{
				return m_perspectiveProjectionMatrix;
			}

			float ViewFrustum::GetFieldOfView() const
			{
				return m_fieldOfView;
			}

			void ViewFrustum::SetFieldOfView(float fox)
			{
				m_fieldOfView = fox;
				UpdateMatrices();
			}

			int ViewFrustum::GetOffsetX() const
			{
				return m_offsetX;
			}

			void ViewFrustum::SetOffsetX(int offsetX)
			{
				m_offsetX = offsetX;
			}

			int ViewFrustum::GetOffsetY() const
			{
				return m_offsetY;
			}

			void ViewFrustum::SetOffsetY(int offsetY)
			{
				m_offsetY = offsetY;
			}

			int ViewFrustum::GetWidth() const
			{
				return m_width;
			}

			void ViewFrustum::SetWidth(int w)
			{
				m_width = w;
				UpdateMatrices();
			}

			int ViewFrustum::GetHeight() const
			{
				return m_height;
			}

			void ViewFrustum::SetHeight(int h)
			{
				m_height = h;
				UpdateMatrices();
			}

			float ViewFrustum::GetNearClippingPlane() const
			{
				return m_nearClippingPlane;
			}

			void ViewFrustum::SetNearClippingPlane(float n)
			{
				m_nearClippingPlane = n;
				UpdateMatrices();
			}

			float ViewFrustum::GetFarClippingPlane() const
			{
				return m_farClippingPlane;
			}

			void ViewFrustum::SetFarClippingPlane(float f)
			{
				m_farClippingPlane = f;
				UpdateMatrices();
			}

			void ViewFrustum::Resize(int offsetX, int offsetY, int width, int height)
			{
				m_offsetX = offsetX;
				m_offsetY = offsetY;
				m_width = width;
				m_height = height;
				glViewport(offsetX, offsetY, m_width, m_height);
				UpdateMatrices();
			}

			void ViewFrustum::ResizeToFull()
			{
				glViewport(m_offsetX, m_offsetY, m_width, m_height);
				UpdateMatrices();
			}
		}
	}
}