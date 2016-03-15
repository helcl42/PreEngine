#ifndef BASE_SCENE_NODE_H
#define BASE_SCENE_NODE_H

#include <PreEngine/Render/SceneNode.h>
#include <PreEngine/Windows/WindowEvents.h>
#include <PreEngine/Render/Shaders/ShaderProgramBuilder.h>

#include "../Events/RenderStateChangeEvent.h"

namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Core;
		using namespace PreEngine::Windows::Events;

		using namespace TestScene::Events;

		template <class NodeType, class RootType>
		class BaseSceneNode : public SceneNode<NodeType, RootType>
		{
		private:
			EventHandler<BaseSceneNode, OnReset>* m_resetOpenGLHandler;

			EventHandler<BaseSceneNode, RenderStateChangeEvent>* m_stateChangeHandler;

		protected:
			IShaderProgramBuilder* m_programBuilder;

			glm::mat4 m_model;

			glm::mat4 m_lightProjectionViewMatrix;

			glm::mat4 m_projection;

			glm::mat4 m_view;

			glm::mat4 m_previousModelViewProjectionMatrix;

			RenderPassType m_renderPassType;

			bool m_showNormals;

			bool m_useBumpMaps;

			float m_normalLength;

			Material m_shinyMaterial;

		public:
			BaseSceneNode(RootType* root);

			virtual ~BaseSceneNode();

		protected:
			void SetMatrices(IShaderProgram* program);

			glm::mat4 GetModelViewProjectionMatrix() const;

		public:
			virtual void operator()(const OnReset& resetOpenGL); // can be overriden by subclass

			virtual void operator()(const RenderStateChangeEvent& matrices); // can be overriden by subclass
		};


		template <class NodeType, class RootType>
		BaseSceneNode<NodeType, RootType>::BaseSceneNode(RootType* root)
			: SceneNode<NodeType, RootType>(root), m_useBumpMaps(true), m_showNormals(false), m_normalLength(1.0f)
		{
			m_resetOpenGLHandler = new EventHandler<BaseSceneNode, OnReset>(this);
			m_stateChangeHandler = new EventHandler<BaseSceneNode, RenderStateChangeEvent>(this);
			m_programBuilder = new ShaderProgramBuilder();
		}

		template <class NodeType, class RootType>
		BaseSceneNode<NodeType, RootType>::~BaseSceneNode()
		{
			SAFE_DELETE(m_programBuilder);
			SAFE_DELETE(m_stateChangeHandler);
			SAFE_DELETE(m_resetOpenGLHandler);
		}

		template <class NodeType, class RootType>
		void BaseSceneNode<NodeType, RootType>::SetMatrices(IShaderProgram* program)
		{
			program->SetUniform("matrices.modelMatrix", m_model);
			program->SetUniform("matrices.modelViewMatrix", m_view * m_model);
			program->SetUniform("matrices.modelViewProjectionMatrix", m_projection * m_view * m_model);
			program->SetUniform("matrices.viewMatrix", m_view);
			program->SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(m_model)));
			program->SetUniform("matrices.projectionMatrix", m_projection);
			program->SetUniform("matrices.shadowMatrix", m_lightProjectionViewMatrix * m_model);
			program->SetUniform("matrices.previousModelViewProjectionMatrix", m_previousModelViewProjectionMatrix);
		}

		template <class NodeType, class RootType>
		glm::mat4 BaseSceneNode<NodeType, RootType>::GetModelViewProjectionMatrix() const
		{
			return m_projection * m_view * m_model;
		}

		template <class NodeType, class RootType>
		void BaseSceneNode<NodeType, RootType>::operator()(const OnReset& resetOpenGL) // can be overriden by subclass
		{
			if (IsRoot())
			{
				ShutDown();
				Init();
			}
		}

		template <class NodeType, class RootType>
		void BaseSceneNode<NodeType, RootType>::operator()(const RenderStateChangeEvent& renderState) // can be overriden by subclass
		{
			m_renderPassType = renderState.renderPassType;
			m_projection = renderState.projectionMatrix;
			m_view = renderState.viewMatrix;
			m_lightProjectionViewMatrix = renderState.lightProjectionViewMatrix;
			m_useBumpMaps = renderState.useBumpMaps;
			m_showNormals = renderState.showNormals;
			m_normalLength = renderState.normalLength;
			m_shinyMaterial = renderState.shinyMaterial;
		}
	}
}

#endif