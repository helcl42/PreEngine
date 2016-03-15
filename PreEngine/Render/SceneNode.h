#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "../Core/Common.h"
#include "../Core/Events/CoreEvents.h"
#include "../Inputs/Core/Keyboards/KeyboardEvents.h"
#include "../Inputs/Core/Mouses/MouseEvents.h"
#include "../Render/Frustums/ViewFrustumEvents.h"

#include "ISceneNode.h"
#include "Shaders/ShaderProgram.h"
#include "Shaders/ShaderFactory.h"
#include "Frustums/ViewFrustum.h"
#include "SceneLayout.h"
#include "ScenePosition.h"
#include "../Core/Object.h"

namespace PreEngine
{
	namespace Render
	{
		using namespace PreEngine::Core;
		using namespace PreEngine::Core::Events;
		using namespace PreEngine::Render::Frustums::Events;
		using namespace PreEngine::Render::Shaders;

		template <class ObjectType, class RootType>
		class SceneNode : public Object<ObjectType>, public ISceneNode<RootType>
		{
		protected:
			EventHandler<SceneNode, OnViewFrustumChange>* m_viewFrustumChangeHandler;

			unsigned int m_sceneId;

			unsigned int m_width;

			unsigned int m_height;

			glm::mat4 m_perspectiveProjectionMatrix;

			glm::mat4 m_orthographicProjectionMatrix;

			SceneLayout m_sceneLayout;

			ScenePosition m_scenePosition;


			std::string m_tag;

			RootType* m_root;

			std::vector<ISceneNode<RootType>*> m_children;

			float m_deltaTime;

		public:
			SceneNode(unsigned int sceneId = 0, enum ScenePosition position = ScenePosition::NONE);

			SceneNode(RootType* root, unsigned int sceneId = 0, enum ScenePosition position = ScenePosition::NONE);

			virtual ~SceneNode();

		private:
			void FindByTag(const std::string& tag, ISceneNode<RootType>* root, std::vector<ISceneNode<RootType>*>& resultNodes) const;

			ISceneNode<RootType>* FindSingleByTag(const std::string& tag, ISceneNode<RootType>* root) const;

			template <class SearchedType>
			void FindByType(ISceneNode<RootType>* root, std::vector<SearchedType*>& resultNodes) const;

			template <class SearchedType>
			SearchedType* FindSingleByType(ISceneNode<RootType>* root) const;

		public:
			bool IsRealMaster() const;

			bool IsMaster() const;

			bool IsSlave() const;

			ScenePosition GetScenePosition() const;

			const glm::mat4& GetPerspectiveProjectionMatrix() const;

			const glm::mat4& GetOrthographicProjectionMatrix() const;

			const std::vector<ISceneNode<RootType>*>& GetChildren() const;

			RootType* GetRoot() const;

			void SetRoot(RootType* root);

			bool IsRoot() const;

			bool IsLeaf() const;

			const std::string& GetTag() const;

			void SetTag(const std::string& tag);

			void AddChild(ISceneNode<RootType>* child);

			std::vector<ISceneNode<RootType>*> FindByTag(const std::string& tag) const;
			
			ISceneNode<RootType>* FindSingleByTag(const std::string& tag) const;

			template <class SearchedType>
			std::vector<SearchedType*> FindByType() const;

			template <class SearchedType>
			SearchedType* FindSingleByType() const;

		public: // overrideable
			std::string GetInfo() const;

		public:
			void operator()(const OnViewFrustumChange& frustum);
		};

		template <class ObjectType, class RootType>
		SceneNode<ObjectType, RootType>::SceneNode(unsigned int sceneId, enum ScenePosition position)
			: m_sceneId(sceneId), m_scenePosition(position), m_root(NULL)
		{
			m_tag = m_name;
			m_viewFrustumChangeHandler = new EventHandler<SceneNode, OnViewFrustumChange>(this);
		}

		template <class ObjectType, class RootType>
		SceneNode<ObjectType, RootType>::SceneNode(RootType* root, unsigned int sceneId, enum ScenePosition position)
			: SceneNode<ObjectType, RootType>(sceneId, position)
		{
			m_root = root;
		}

		template <class ObjectType, class RootType>
		SceneNode<ObjectType, RootType>::~SceneNode()
		{
			SAFE_DELETE(m_viewFrustumChangeHandler);

			/*for (std::vector<ISceneNode<RootType>*>::iterator ii = m_children.begin(); ii != m_children.end(); ii++)
			{
				SAFE_DELETE(*ii);
			}*/
		}

		template <class ObjectType, class RootType>
		bool SceneNode<ObjectType, RootType>::IsRealMaster() const
		{
			return (m_scenePosition == ScenePosition::LEFT || m_scenePosition == ScenePosition::TOP || m_scenePosition == ScenePosition::NONE) && m_sceneId == 0;
		}

		template <class ObjectType, class RootType>
		bool SceneNode<ObjectType, RootType>::IsMaster() const
		{
			return m_scenePosition == ScenePosition::LEFT || m_scenePosition == ScenePosition::TOP || (m_scenePosition == ScenePosition::NONE && m_sceneId == 0);
		}

		template <class ObjectType, class RootType>
		bool SceneNode<ObjectType, RootType>::IsSlave() const
		{
			return (m_scenePosition == ScenePosition::RIGHT || m_scenePosition == ScenePosition::BOTTOM) && m_sceneId != 0;
		}

		template <class ObjectType, class RootType>
		ScenePosition SceneNode<ObjectType, RootType>::GetScenePosition() const
		{
			return m_scenePosition;
		}

		template <class ObjectType, class RootType>
		void SceneNode<ObjectType, RootType>::operator()(const OnViewFrustumChange& frustum)
		{
			if (frustum.sceneId == m_sceneId)
			{
				m_width = frustum.width;
				m_height = frustum.height;
				m_perspectiveProjectionMatrix = frustum.projectionMatrix;
				m_orthographicProjectionMatrix = frustum.orthoMatrix;
			}
		}

		template <class ObjectType, class RootType>
		const glm::mat4& SceneNode<ObjectType, RootType>::GetPerspectiveProjectionMatrix() const
		{
			return m_perspectiveProjectionMatrix;
		}

		template <class ObjectType, class RootType>
		const glm::mat4& SceneNode<ObjectType, RootType>::GetOrthographicProjectionMatrix() const
		{
			return m_orthographicProjectionMatrix;
		}

		template <class ObjectType, class RootType>
		const std::vector<ISceneNode<RootType>*>& SceneNode<ObjectType, RootType>::GetChildren() const
		{
			return m_children;
		}

		template <class ObjectType, class RootType>
		RootType* SceneNode<ObjectType, RootType>::GetRoot() const
		{
			return m_root;
		}

		template <class ObjectType, class RootType>
		void SceneNode<ObjectType, RootType>::SetRoot(RootType* root)
		{
			m_root = root;
		}

		template <class ObjectType, class RootType>
		bool SceneNode<ObjectType, RootType>::IsRoot() const
		{
			return m_root == dynamic_cast<const RootType*>(this);	// TODO check IT !!
		}

		template <class ObjectType, class RootType>
		bool SceneNode<ObjectType, RootType>::IsLeaf() const
		{
			return m_children.size() == 0;
		}

		template <class ObjectType, class RootType>
		std::string SceneNode<ObjectType, RootType>::GetInfo() const
		{
			return std::string();
		}

		template <class ObjectType, class RootType>
		const std::string& SceneNode<ObjectType, RootType>::GetTag() const
		{
			return m_tag;
		}

		template <class ObjectType, class RootType>
		void SceneNode<ObjectType, RootType>::SetTag(const std::string& tagName)
		{
			m_tag = tagName;
		}

		template <class ObjectType, class RootType>
		void SceneNode<ObjectType, RootType>::AddChild(ISceneNode<RootType>* child)
		{
			m_children.push_back(child);
		}

		template <class ObjectType, class RootType>
		void SceneNode<ObjectType, RootType>::FindByTag(const std::string& tag, ISceneNode<RootType>* root, std::vector<ISceneNode<RootType>*>& resultNodes) const
		{
			if (root->GetTag() == tag) resultNodes.push_back(root);

			const std::vector<ISceneNode<RootType>*>& children = root->GetChildren();
			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = children.cbegin(); ii != children.cend(); ++ii)
			{
				if ((*ii)->GetTag() == tag) resultNodes.push_back(*ii);
				FindByTag(tag, *ii, resultNodes);
			}
		}

		template <class ObjectType, class RootType>
		std::vector<ISceneNode<RootType>*> SceneNode<ObjectType, RootType>::FindByTag(const std::string& tag) const
		{
			std::vector<ISceneNode<RootType>*> resultNodes;
			FindByTag(tag, m_root, resultNodes);
			return resultNodes;
		}

		template <class ObjectType, class RootType>
		ISceneNode<RootType>* SceneNode<ObjectType, RootType>::FindSingleByTag(const std::string& tag, ISceneNode<RootType>* root) const
		{
			if (root->GetTag() == tag) return root;

			const std::vector<ISceneNode<RootType>*>& children = root->GetChildren();
			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = children.cbegin(); ii != children.cend(); ++ii)
			{
				if ((*ii)->GetTag() == tag) return *ii;
				ISceneNode<RootType>* node = FindSingleByTag(tag, *ii);
				if (node != NULL) return node;
			}
			return NULL;
		}

		template <class ObjectType, class RootType>
		ISceneNode<RootType>* SceneNode<ObjectType, RootType>::FindSingleByTag(const std::string& tag) const
		{
			return FindSingleByTag(tag, m_root);
		}

		template <class ObjectType, class RootType>
		template <class SearchedType>
		void SceneNode<ObjectType, RootType>::FindByType(ISceneNode<RootType>* root, std::vector<SearchedType*>& resultNodes) const
		{
			SearchedType* node = dynamic_cast<SearchedType*>(root);
			if (node) resultNodes.push_back(node);

			const std::vector<ISceneNode<RootType>*>& children = root->GetChildren();
			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = children.cbegin(); ii != children.cend(); ++ii)
			{
				node = dynamic_cast<SearchedType*>(*ii);
				if (node) resultNodes.push_back(node);
				FindByType(*ii, resultNodes);
			}
		}

		template <class ObjectType, class RootType>
		template <class SearchedType>
		std::vector<SearchedType*> SceneNode<ObjectType, RootType>::FindByType() const
		{
			std::vector<SearchedType*> resultNodes;
			FindByType<SearchedType>(m_root, resultNodes);
			return resultNodes;
		}

		template <class ObjectType, class RootType>
		template <class SearchedType>
		SearchedType* SceneNode<ObjectType, RootType>::FindSingleByType(ISceneNode<RootType>* root) const
		{
			if (root == NULL) return NULL;

			SearchedType* node = dynamic_cast<SearchedType*>(root);
			if (node != NULL) return node;

			const std::vector<ISceneNode<RootType>*>& children = root->GetChildren();
			for (std::vector<ISceneNode<RootType>*>::const_iterator ii = children.cbegin(); ii != children.cend(); ++ii)
			{
				node = dynamic_cast<SearchedType*>(*ii);
				if (node != NULL) return node;
				node = FindSingleByType<SearchedType>(*ii);
				if (node != NULL) return node;
			}
			return NULL;
		}

		template <class ObjectType, class RootType>
		template <class SearchedType>
		SearchedType* SceneNode<ObjectType, RootType>::FindSingleByType() const
		{
			return FindSingleByType<SearchedType>(m_root);
		}
	}
}

#endif