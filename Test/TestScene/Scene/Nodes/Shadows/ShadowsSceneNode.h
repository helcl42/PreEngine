#ifndef SHADOWS_SCENE_NODE_H
#define SHADOWS_SCENE_NODE_H

#include <PreEngine/Render/Effects/Shadows.h>

#include "../BaseSceneNode.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Effects;

		template <class RootType>
		class ShadowsSceneNode : public BaseSceneNode<ShadowsSceneNode<RootType>, RootType>
		{
		private:
			Shadows* m_shadows;

			IShaderProgram* m_mainProgram;

		public:
			ShadowsSceneNode(RootType* root)
				: BaseSceneNode<ShadowsSceneNode<RootType>, RootType>(root)
			{
				m_shadows = new Shadows(m_sceneId, 4096, true, false);
			}

			virtual ~ShadowsSceneNode()
			{
				SAFE_DELETE(m_shadows);
				SAFE_DELETE(m_mainProgram);
			}

		public:
			void Init()
			{
				m_shadows->Init();

				m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/ShadowsShader.bin");
				m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Effects/ShadowsDepthStore.vert.hlsl");
				m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Effects/ShadowsDepthStore.frag.hlsl");
				m_mainProgram = m_programBuilder->Build(true, false);

				m_mainProgram->Use();
				m_shadows->SetTextureUnit(0);
				m_shadows->SetUniformData(m_mainProgram, "shadows");
				m_mainProgram->Validate();
			}

			std::string GetInfo() const
			{
				std::stringstream ss;
				ss << "Shadows: " << (m_shadows->AreShadowOn() ? "ON" : "OFF") << std::endl;
				ss << "Use Hard Shadows: " << (m_shadows->AreUsedHardShadows() ? "YES" : "NO") << std::endl;
				ss << "---------------------------------------" << std::endl;
				return std::string(ss.str());
			}

			void Update(float deltaTime)
			{
				m_deltaTime = deltaTime;
			}

			void PreRender()
			{
				m_mainProgram->Use();
				m_shadows->SetTextureUnit(0);
				m_shadows->SetUniformData(m_mainProgram, "shadows");
				m_shadows->BindFrameBuffer();
				glClear(GL_DEPTH_BUFFER_BIT);
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "RecordDepth");
			}

			void Render()
			{
				FrameBuffer::BindDefaultFrameBuffer(m_sceneId, m_width, m_height);

				m_mainProgram->Use();
				m_mainProgram->ActivateSubroutine(ShaderType::FRAGMENT_SHADER, "ShadeWithShadow");
			}

			void PostRender()
			{
			}

			void ShutDown()
			{
				m_shadows->ShutDown();

				m_mainProgram->DeleteShaders();
				m_mainProgram->Delete();
				SAFE_DELETE(m_mainProgram);
			}

			Shadows* GetShadows() const
			{
				return m_shadows;
			}
		};
	}
}

#endif