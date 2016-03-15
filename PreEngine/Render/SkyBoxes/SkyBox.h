#ifndef SKY_BOX_H
#define SKY_BOX_H

#include "../../Core/Common.h"
#include "../../Render/VertexBufferObjects/VertexBufferObject.h"
#include "../../Render/Textures/Texture.h"
#include "../../Render/Textures/TextureFactory.h"

#include "ISkyBox.h"
#include "SkyBoxFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			using namespace PreEngine::Render::VertexBufferObjects;
			using namespace PreEngine::Render::Textures;

			class SkyBox : public ISkyBox
			{
			private:
				friend class SkyBoxFactory;

			private:
				GLuint m_vertexArrayObject;

				IVertexBufferObject* m_vbo;

				ITexture* m_textures[6];

				std::string m_directory;

				std::string m_front, m_back, m_left, m_right, m_top, m_bottom;

			public:
				SkyBox();

				virtual ~SkyBox();

			public:
				void Render();

				void Delete();
			};
		}
	}
}

#endif