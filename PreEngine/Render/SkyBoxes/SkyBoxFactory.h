#ifndef SKY_BOX_FACTORY_H
#define SKY_BOX_FACTORY_H

#include "SkyBox.h"
#include "ISkyBoxFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			using namespace PreEngine::Render::Textures;

			class SkyBoxFactory : public ISkyBoxFactory
			{
			private:
				ITextureFactory* m_textureFactory;

			public:
				SkyBoxFactory();

				virtual ~SkyBoxFactory();

			public:
				ISkyBox* CreateSkyBox(std::string dir, std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom);
			};
		}
	}
}

#endif