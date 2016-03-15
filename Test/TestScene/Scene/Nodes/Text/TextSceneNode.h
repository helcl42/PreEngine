#ifndef FONT_COMPONENT_H
#define FONT_COMPONENT_H

#include <PreEngine/Core/Common.h>
#include <PreEngine/Render/Fonts/FontFactory.h>
#include <PreEngine/Render/SceneNode.h>

#include "TextData.h"


namespace TestScene
{
	namespace Nodes
	{
		using namespace PreEngine::Render;
		using namespace PreEngine::Render::Fonts;

		template <class RootType>
		class TextSceneNode : public BaseSceneNode<TextSceneNode<RootType>, RootType>
		{
		private:
			IFontFactory* m_fontFactory;

			IFont* m_font;

			IShaderProgram* m_fontProgram;

			std::string m_fontPath;

			unsigned int m_fontSize;

			std::string m_fpsMessage;

			std::string m_controlMessage;

			std::queue<TextData> m_messageQueue;

		public:
			TextSceneNode(RootType* root, unsigned int fontSize);

			TextSceneNode(RootType* root, std::string path, unsigned int fontSize);

			virtual ~TextSceneNode();

		public:
			void Init();

			void Update(float deltaTime);

			void AddMessage(const TextData& data);

			void ClearMessages();

			unsigned int GetTextWidth(const std::string& text, int pxSize);

			unsigned int GetTextHeight(const std::string& text, int pxSize);

			void PreRender();

			void Render();

			void PostRender();

			void ShutDown();
		};


		template <class RootType>
		TextSceneNode<RootType>::TextSceneNode(RootType* root, unsigned int fontSize)
			: TextSceneNode<RootType>(root, "C:/Windows/Fonts/arial.ttf", fontSize)
		{
		}

		template <class RootType>
		TextSceneNode<RootType>::TextSceneNode(RootType* root, std::string path, unsigned int fontSize)
			: BaseSceneNode<TextSceneNode<RootType>, RootType>(root), m_fontPath(path), m_fontSize(fontSize)
		{
			m_fontFactory = new FontFactory();
		}

		template <class RootType>
		TextSceneNode<RootType>::~TextSceneNode()
		{
			SAFE_DELETE(m_font);
			SAFE_DELETE(m_fontFactory);
			SAFE_DELETE(m_fontProgram);
		}

		template <class RootType>
		void TextSceneNode<RootType>::Init()
		{
			m_programBuilder->SetBinaryPath("./TestScene/Assets/Shaders/Binary/FontShader.bin");
			m_programBuilder->AddShader(ShaderType::VERTEX_SHADER, "./TestScene/Assets/Shaders/Font/2DFont.vert.hlsl");
			m_programBuilder->AddShader(ShaderType::FRAGMENT_SHADER, "./TestScene/Assets/Shaders/Font/2DFont.frag.hlsl");
			m_fontProgram = m_programBuilder->Build();

			m_font = m_fontFactory->CreateFreeTypeFont(m_fontPath, m_fontSize);
			m_font->SetShaderProgram(m_fontProgram);
		}

		template <class RootType>
		void TextSceneNode<RootType>::Update(float deltaTime)
		{
			m_deltaTime = deltaTime;
		}

		template <class RootType>
		void TextSceneNode<RootType>::AddMessage(const TextData& data)
		{
			m_messageQueue.push(data);
		}

		template <class RootType>
		void TextSceneNode<RootType>::ClearMessages()
		{
			std::queue<TextData> empty;
			std::swap(m_messageQueue, empty);
		}

		template <class RootType>
		unsigned int TextSceneNode<RootType>::GetTextWidth(const std::string& text, int pxSize)
		{
			return m_font->GetTextWidth(text, pxSize);
		}

		template <class RootType>
		unsigned int TextSceneNode<RootType>::GetTextHeight(const std::string& text, int pxSize)
		{
			return m_font->GetTextHeight(text, pxSize);
		}

		template <class RootType>
		void TextSceneNode<RootType>::PreRender()
		{
		}

		template <class RootType>
		void TextSceneNode<RootType>::Render()
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDisable(GL_DEPTH_TEST);

			m_fontProgram->Use();
			m_fontProgram->SetUniform("projectionMatrix", m_orthographicProjectionMatrix);

			while (!m_messageQueue.empty())
			{
				TextData current = m_messageQueue.front();
				m_fontProgram->SetUniform("color", current.color);
				m_font->Print(current.message, current.positionX, current.positionY, current.size);
				m_messageQueue.pop();
			}

			glEnable(GL_DEPTH_TEST);
		}

		template <class RootType>
		void TextSceneNode<RootType>::PostRender()
		{
		}

		template <class RootType>
		void TextSceneNode<RootType>::ShutDown()
		{
			m_font->Delete();

			m_fontProgram->Delete();
			m_fontProgram->DeleteShaders();
			SAFE_DELETE(m_fontProgram);
		}
	}
}

#endif