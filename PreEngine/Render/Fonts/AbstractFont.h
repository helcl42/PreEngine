#ifndef ABSTRACT_FONT_H
#define ABSTRACT_FONT_H

#include "../VertexBufferObjects/VertexBufferObject.h"
#include "../Textures/Texture.h"
#include "../Textures/TextureFactory.h"
#include "../Shaders/ShaderProgram.h"

#include "IFont.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			using namespace PreEngine::Render::VertexBufferObjects;

			class AbstractFont : public IFont
			{
			protected:
				GLuint m_vertexAttributeObject;

				IVertexBufferObject* m_vbo;

				IShaderProgram* m_program;

				int m_loadedPixelSize;


			public:
				AbstractFont();

				virtual ~AbstractFont();
			};
		}
	}
}

#endif