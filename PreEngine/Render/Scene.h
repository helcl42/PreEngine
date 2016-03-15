#ifndef BASIC_SCENE_H
#define BASIC_SCENE_H

#include "IScene.h"
#include "AbstractScene.h"

namespace PreEngine
{
	namespace Render
	{
		template <class RootType>
		class Scene : public AbstractScene<RootType>
		{
		private:
			std::vector<ISceneNode<RootType>*> m_nodes;

		public:
			Scene(unsigned int sceneId, SceneItemConfig* sceneConfig);

			virtual ~Scene();

		public:
			bool Init();

			void Update(float deltaTime);

			void Render();

			void ShutDown();

			void AddSceneNode(ISceneNode<RootType>* node);
		};

		template <class RootType>
		Scene<RootType>::Scene(unsigned int sceneId, SceneItemConfig* sceneConfig)
			: AbstractScene(sceneId, sceneConfig)
		{
		}

		template <class RootType>
		Scene<RootType>::~Scene()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				SAFE_DELETE(*ii);
			}
		}

		template <class RootType>
		bool Scene<RootType>::Init()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->Init();
			}

			return true;
		}

		template <class RootType>
		void Scene<RootType>::Update(float deltaTime)
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->Update(deltaTime);
			}
		}

		template <class RootType>
		void Scene<RootType>::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->PreRender();
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->Render();
			}

			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->PostRender();
			}

			glFinish();
		}

		template <class RootType>
		void Scene<RootType>::ShutDown()
		{
			for (std::vector<ISceneNode<RootType>*>::iterator ii = m_nodes.begin(); ii != m_nodes.end(); ii++)
			{
				(*ii)->ShutDown();
			}
		}

		template <class RootType>
		void Scene<RootType>::AddSceneNode(ISceneNode<RootType>* node)
		{
			m_nodes.push_back(node);
		}
	}
}

#endif