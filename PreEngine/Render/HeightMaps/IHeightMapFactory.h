#ifndef IHEIGHT_MAP_FACTORY_H
#define IHEIGHT_MAP_FACTORY_H

#include "IHeightMap.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			class IHeightMapFactory
			{
			public:
				virtual IHeightMap* CreateHeightMap(const std::string& textureFilePath) = 0;

			public:
				virtual ~IHeightMapFactory() {}
			};
		}
	}
}

#endif