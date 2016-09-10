#ifndef ISCENE_H
#define ISCENE_H

#include "ScenePosition.h"
#include "ISceneNode.h"
#include "SceneEye.h"

namespace PreEngine
{
	namespace Render
	{
		template <class RootType>
		class IScene
		{
		public:
			virtual bool Init() = 0;

			virtual void Update(float deltaTime) = 0;

			virtual void Render() = 0;

			virtual void ShutDown() = 0;

			virtual void AddSceneNode(ISceneNode<RootType>* node) = 0;

			virtual unsigned int GetSceneId() const = 0;

			virtual unsigned int GetWidth() const = 0;

			virtual unsigned int GetHeight() const = 0;

			virtual SceneEye GetSceneEye() const = 0;

		public:
			virtual ~IScene() {}
		};
	}
}

#endif