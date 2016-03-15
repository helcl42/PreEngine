#ifndef ABSTRACT_MODEL_FACTORY_H
#define ABSTRACT_MODEL_FACTORY_H

#include "../Textures/TextureFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			using namespace PreEngine::Render::Textures;

			class AbstractModelFactory
			{
			protected:
				ITextureFactory* m_textureFactory;

			public:
				AbstractModelFactory()
				{
					m_textureFactory = new TextureFactory();
				}

				virtual ~AbstractModelFactory()
				{
					SAFE_DELETE(m_textureFactory);
				}
			};
		}
	}
}

#endif