#ifndef CAMERA_SCENE_NODE_H
#define CAMERA_SCENE_NODE_H

#include <PreEngine/Render/Cameras/FlyingCamera.h>

#include "../BaseSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Cameras;

		template <class RootType>
		class CameraSceneNode : public BaseSceneNode<CameraSceneNode<RootType>, RootType>
		{
		private:
			IFlyingCamera* m_flyingCamera;

		public:
			CameraSceneNode(RootType* root)
				: BaseSceneNode<CameraSceneNode<RootType>, RootType>(root)
			{
			}

			virtual ~CameraSceneNode()
			{
				SAFE_DELETE(m_flyingCamera);
			}

		public:
			void Init()
			{
				m_flyingCamera = new FlyingCamera(glm::vec3(-75.0f, 10.0f, 120.0f), glm::vec3(-75.0f, 10.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.0f), 25.0f, 0.001f);
				m_flyingCamera->SetMovingKeys(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D);
			}

			std::string GetInfo() const
			{
				glm::vec3 eye = m_flyingCamera->GetEye();
				glm::vec3 view = m_flyingCamera->GetView();

				std::stringstream ss;
				ss << "Cam EYE: [" << eye.x << ", " << eye.y << ", " << eye.z << "]" << std::endl;
				ss << "Cam VIEW: [" << view.x << ", " << view.y << ", " << view.z << "]" << std::endl;
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
				m_flyingCamera->Update(deltaTime);
			}

			void PreRender()
			{
			}

			void PostRender()
			{
			}

			void Render()
			{
			}

			void ShutDown()
			{
			}

			IFlyingCamera* GetCamera() const
			{
				return m_flyingCamera;
			}
		};
	}
}

#endif