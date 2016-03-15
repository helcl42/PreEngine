#ifndef FONT_H
#define FONT_H

#include "../../../Core/Common.h"

#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Textures/Texture.h"
#include "../../Textures/TextureFactory.h"
#include "../../Shaders/ShaderProgram.h"

#include "../AbstractFont.h"
#include "../FontException.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			using namespace PreEngine::Render::Textures;
			using namespace PreEngine::Render::Shaders;

			class SimpleFont : public AbstractFont
			{
			private:
				friend class FontFactory;

			private:
				ITexture* m_fontTexture;

				unsigned int m_rows;

				unsigned int m_colums;

			public:
				SimpleFont();

				virtual ~SimpleFont();

			private:
				unsigned int PrepareData(const std::string& text, int x, int y, int size);

			public:
				unsigned int GetTextWidth(const std::string& text, int pxSize);

				unsigned int GetTextHeight(const std::string& text, int pxSize);

				void Print(const std::string& text, int x, int y, int size = -1);

				void Delete();

				void SetShaderProgram(IShaderProgram* shaderProgram);
			};
		}
	}
}

#endif