#ifndef HEIGHT_MAP_FACTORY_H
#define HEIGHT_MAP_FACTORY_H

#include "IHeightMapFactory.h"
#include "HeightMap.h"
#include "HeightMapException.h"
#include <FreeImage.h>

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			class HeightMapFactory : public IHeightMapFactory
			{
			private:
				unsigned int m_pixelStep;

				unsigned int m_pixelRowStep;

				unsigned int m_rows;

				unsigned int m_cols;

				std::vector<std::vector<glm::vec3>> m_vertexData;

				std::vector<std::vector<glm::vec2>> m_textureCoordsData;

				std::vector<std::vector<glm::vec3>> m_normals;


			public:
				HeightMapFactory();

				virtual ~HeightMapFactory();

			private:
				FIBITMAP* GetImage(std::string filePath);

				void ReadImageData(unsigned char* data);

				void GenerateNormals();

				void FillHeightMapVBO(HeightMap* heightMap);

				void FillHeightMapIndicesVBO(HeightMap* heightMap);

				void BindHeightMapData(HeightMap* heightMap);

				void InvalidateState();

			public:
				IHeightMap* CreateHeightMap(const std::string filePath);
			};
		}
	}
}

#endif