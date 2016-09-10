#ifndef ISCENE_NODE_H
#define ISCENE_NODE_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		template <class RootType>
		class ISceneNode
		{
		public:
			virtual void Init() = 0;

			virtual void Update(float deltaTime) = 0;

			virtual void PreRender() = 0;

			virtual void Render() = 0;

			virtual void PostRender() = 0;

			virtual void ShutDown() = 0;

			virtual bool IsMaster() const = 0;

			virtual bool IsSlave() const = 0;

			virtual ScenePosition GetScenePosition() const = 0;

			virtual const std::vector<ISceneNode<RootType>*>& GetChildren() const = 0;

			virtual void AddChild(ISceneNode<RootType>* child) = 0;

			virtual std::vector<ISceneNode<RootType>*> FindByTag(const std::string& tag) const = 0;

			virtual ISceneNode<RootType>* FindSingleByTag(const std::string& tag) const = 0;

			virtual const glm::mat4& GetPerspectiveProjectionMatrix() const = 0;

			virtual const glm::mat4& GetOrthographicProjectionMatrix() const = 0;

			virtual RootType* GetRoot() const = 0;

			virtual void SetRoot(RootType* root) = 0;

			virtual bool IsRoot() const = 0;

			virtual bool IsLeaf() const = 0;

			virtual std::string GetInfo() const = 0;

			virtual const std::string& GetTag() const = 0;

			virtual void SetTag(const std::string& tag) = 0;

			virtual void SetEnabled(bool enabled) = 0;

			virtual bool IsEnabled() const = 0;

		public:
			virtual ~ISceneNode() {}
		};
	}
}

#endif