#ifndef ISKYBOX_FACTORY
#define ISKYBOX_FACTORY

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			class ISkyBoxFactory
			{
			public:
				virtual ISkyBox* CreateSkyBox(std::string dir, std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom) = 0;

			public:
				virtual ~ISkyBoxFactory() {}
			};
		}
	}
}

#endif