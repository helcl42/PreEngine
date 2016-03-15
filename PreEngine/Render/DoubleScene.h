#ifndef DOUBLE_SCENE_H
#define DOUBLE_SCENE_H

#include "IScene.h"
#include "AbstractScene.h"

namespace PreEngine
{
	namespace Render
	{
		template <class RootType>
		class DoubleScene : public AbstractScene<RootType>
		{
		private:
			std::vector<ISceneNode<RootType>*> m_leftNodes;

			std::vector<ISceneNode<RootType>*> m_rightNodes;

		public:
			DoubleScene(unsigned int sceneId, SceneItemConfig* sceneConfig);

			virtual ~DoubleScene();

		private:
			void Render(const std::vector<ISceneNode<RootType>*>& nodes);

		public:
			bool Init();

			void Update(float deltaTime);

			void Render();

			void ShutDown();

			void AddSceneNode(ISceneNode<RootType>* node);
		};

		template <class RootType>
		DoubleScene<RootType>::DoubleScene(unsigned int sceneId, SceneItemConfig* sceneConfig)
			: AbstractScene(sceneId, sceneConfig)
		{
		}

		template <class RootType>
		DoubleScene<RootType>::~DoubleScene()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_leftNodes.begin(); ii != m_leftNodes.end(); ii++)
			{
				SAFE_DELETE(*ii);
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_rightNodes.begin(); ii != m_rightNodes.end(); ii++)
			{
				SAFE_DELETE(*ii);
			}
		}

		template <class RootType>
		bool DoubleScene<RootType>::Init()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_leftNodes.begin(); ii != m_leftNodes.end(); ii++)
			{
				(*ii)->Init();
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_rightNodes.begin(); ii != m_rightNodes.end(); ii++)
			{
				(*ii)->Init();
			}

			return true;
		}

		template <class RootType>
		void DoubleScene<RootType>::Update(float deltaTime)
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_leftNodes.begin(); ii != m_leftNodes.end(); ii++)
			{
				(*ii)->Update(deltaTime);
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_rightNodes.begin(); ii != m_rightNodes.end(); ii++)
			{
				(*ii)->Update(deltaTime);
			}
		}

		template <class RootType>
		void DoubleScene<RootType>::Render(const std::vector<ISceneNode<RootType>*>& nodes)
		{
			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = nodes.cbegin(); ii != nodes.cend(); ii++)
			{
				(*ii)->PreRender();
			}

			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = nodes.cbegin(); ii != nodes.cend(); ii++)
			{
				(*ii)->Render();
			}

			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = nodes.cbegin(); ii != nodes.cend(); ii++)
			{
				(*ii)->PostRender();
			}
		}

		template <class RootType>
		void DoubleScene<RootType>::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (m_sceneLayout == SceneLayout::SIDE_BY_SIDE)
			{
				EventChannel::Broadcast(OnViewPortChange{ (int)m_sceneId, 0, 0, int(m_width / 2), int(m_height), SceneLayout::SIDE_BY_SIDE, ScenePosition::LEFT });
				Render(m_leftNodes);

				EventChannel::Broadcast(OnViewPortChange{ (int)m_sceneId, int(m_width / 2), 0, int(m_width / 2), int(m_height), SceneLayout::SIDE_BY_SIDE, ScenePosition::RIGHT });
				Render(m_rightNodes);
			}
			else
			{
				EventChannel::Broadcast(OnViewPortChange{ (int)m_sceneId, 0, int(m_height / 2), int(m_width), int(m_height / 2), SceneLayout::OVER_UNDER, ScenePosition::TOP });
				Render(m_leftNodes);

				EventChannel::Broadcast(OnViewPortChange{ (int)m_sceneId, 0, 0, int(m_width), int(m_height / 2), SceneLayout::OVER_UNDER, ScenePosition::BOTTOM });
				Render(m_rightNodes);
			}

			glFinish();
		}

		template <class RootType>
		void DoubleScene<RootType>::ShutDown()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_leftNodes.begin(); ii != m_leftNodes.end(); ii++)
			{
				(*ii)->ShutDown();
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_rightNodes.begin(); ii != m_rightNodes.end(); ii++)
			{
				(*ii)->ShutDown();
			}
		}

		template <class RootType>
		void DoubleScene<RootType>::AddSceneNode(ISceneNode<RootType>* node)
		{
			if (node->GetScenePosition() == ScenePosition::LEFT || node->GetScenePosition() == ScenePosition::TOP)
			{
				m_leftNodes.push_back(node);
			}
			else
			{
				m_rightNodes.push_back(node);
			}
		}
	}
}

#endif