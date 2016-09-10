#ifndef ABSTRACT_SCENE_H
#define ABSTRACT_SCENE_H

#include "../Core/Common.h"

#include "SceneNode.h"
#include "IScene.h"

#include "../Core/System.h"
#include "../Core/Events/EventHandler.h"
#include "../Inputs/Core/Keyboards/KeyboardEvents.h"
#include "../Inputs/Core/Mouses/MouseEvents.h"
#include "../Core/Events/CoreEvents.h"
#include "../Core/Engines/Config/SceneItemConfig.h"

#include "Frustums/ViewFrustum.h"


namespace PreEngine
{
	namespace Render
	{
		using namespace PreEngine;
		using namespace PreEngine::Core;
		using namespace PreEngine::Core::Engines::Config;
		using namespace PreEngine::Core::Events;
		using namespace PreEngine::Render::Frustums;		

		template <class RootType>
		class AbstractScene : public System, public IScene<RootType>
		{
		protected:
			unsigned int m_width = 0;

			unsigned int m_height = 0;

			unsigned int m_sceneId = 0;

			IViewFrustum* m_viewFrustum;

			EventHandler<AbstractScene<RootType>, Windows::Events::OnResize>* m_resizeHandler;

			SceneEye m_sceneEye;

			SceneItemConfig* m_sceneConfig;

		protected:
			AbstractScene(unsigned int sceneId, SceneItemConfig* sceneConfig);

			virtual ~AbstractScene();

		public:
			unsigned int GetSceneId() const;

			unsigned int GetWidth() const;

			unsigned int GetHeight() const;

			SceneEye GetSceneEye() const;

		public:
			void operator() (const Windows::Events::OnResize& resize);
		};


		template <class RootType>
		AbstractScene<RootType>::AbstractScene(unsigned int sceneId, SceneItemConfig* sceneConfig)
			: m_sceneId(sceneId), m_sceneConfig(sceneConfig)
		{
			m_sceneEye = sceneConfig->GetSceneEye();
			m_resizeHandler = new EventHandler<AbstractScene, Windows::Events::OnResize>(this);

			ViewFrustumConfig* frustumConfig = sceneConfig->GetViewFrustumConfig();
			if (frustumConfig != NULL) m_viewFrustum = new ViewFrustum(sceneId, sceneConfig->GetWidth(), sceneConfig->GetHeight(), frustumConfig->GetFieldOfView(), frustumConfig->GetNearClippingPlane(), frustumConfig->GetFarClippingPlane());
			else m_viewFrustum = new ViewFrustum(sceneId);
		}

		template <class RootType>
		AbstractScene<RootType>::~AbstractScene()
		{
			SAFE_DELETE(m_viewFrustum);
			SAFE_DELETE(m_resizeHandler);
		}

		template <class RootType>
		unsigned int AbstractScene<RootType>::GetSceneId() const
		{
			return m_sceneId;
		}

		template <class RootType>
		unsigned int AbstractScene<RootType>::GetWidth() const
		{
			return m_width;
		}

		template <class RootType>
		unsigned int AbstractScene<RootType>::GetHeight() const
		{
			return m_height;
		}

		template <class RootType>
		SceneEye AbstractScene<RootType>::GetSceneEye() const
		{
			return m_sceneEye;
		}

		template <class RootType>
		void AbstractScene<RootType>::operator() (const Windows::Events::OnResize& resize)
		{
			if (resize.sceneId == m_sceneId)
			{
				m_width = resize.width;
				m_height = resize.height;
			}
		}
	}
}

#endif