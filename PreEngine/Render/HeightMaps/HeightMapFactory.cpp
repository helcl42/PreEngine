#include "HeightMapFactory.h"
#include <FreeImage.h>


namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			HeightMapFactory::HeightMapFactory()
				: m_pixelStep(0), m_pixelRowStep(0), m_rows(0), m_cols(0)
			{
			}

			HeightMapFactory::~HeightMapFactory()
			{
			}

			FIBITMAP* HeightMapFactory::GetImage(std::string filePath)
			{
				FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
				FIBITMAP* dib(0);

				fif = FreeImage_GetFileType(filePath.c_str(), 0);

				if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filePath.c_str());

				if (fif == FIF_UNKNOWN)
					throw HeightMapException("Unknown HeightMap format " + filePath + ".");

				if (FreeImage_FIFSupportsReading(fif))
					dib = FreeImage_Load(fif, filePath.c_str());

				if (!dib)
					throw HeightMapException("Load HeightMap " + filePath + " failed.");

				return dib;
			}

			void HeightMapFactory::ReadImageData(unsigned char* data)
			{
				m_vertexData = std::vector<std::vector<glm::vec3>>(m_rows, std::vector<glm::vec3>(m_cols));
				m_textureCoordsData = std::vector<std::vector<glm::vec2>>(m_rows, std::vector<glm::vec2>(m_cols));

				float textureU = float(m_cols) * 0.1f;
				float textureV = float(m_rows) * 0.1f;

				for (unsigned int i = 0; i < m_rows; i++)
				{
					for (unsigned int j = 0; j < m_cols; j++)
					{
						float scaleCols = float(j) / float(m_cols - 1);
						float scaleRows = float(i) / float(m_rows - 1);
						float vertexHeight = float(data[m_pixelRowStep * i + m_pixelStep * j]) / 255.0f;

						m_vertexData[i][j] = glm::vec3(-0.5f + scaleCols, vertexHeight, -0.5f + scaleRows);
						m_textureCoordsData[i][j] = glm::vec2(textureU * scaleCols, textureV * scaleRows);
					}
				}
			}

			void HeightMapFactory::GenerateNormals()
			{
				std::vector<std::vector<glm::vec3>> normals[2];
				for (unsigned int i = 0; i < 2; i++) normals[i] = std::vector<std::vector<glm::vec3>>(m_rows - 1, std::vector<glm::vec3>(m_cols - 1));

				for (unsigned int i = 0; i < m_rows - 1; i++)
				{
					for (unsigned int j = 0; j < m_cols - 1; j++)
					{
						glm::vec3 triangle0[] = { m_vertexData[i][j], m_vertexData[i + 1][j], m_vertexData[i + 1][j + 1] };
						glm::vec3 triangle1[] = { m_vertexData[i + 1][j + 1], m_vertexData[i][j + 1], m_vertexData[i][j] };

						glm::vec3 triangle0Normal = glm::cross(triangle0[0] - triangle0[1], triangle0[1] - triangle0[2]);
						glm::vec3 triangle1Normal = glm::cross(triangle1[0] - triangle1[1], triangle1[1] - triangle1[2]);

						normals[0][i][j] = glm::normalize(triangle0Normal);
						normals[1][i][j] = glm::normalize(triangle1Normal);
					}
				}

				m_normals = std::vector<std::vector<glm::vec3>>(m_rows, std::vector<glm::vec3>(m_cols));
				for (unsigned int i = 0; i < m_rows; i++)
				{
					for (unsigned int j = 0; j < m_cols; j++)
					{
						glm::vec3 finalNormal(0.0f, 0.0f, 0.0f);

						if (i != 0 && j != 0)
							for (unsigned int k = 0; k < 2; k++) finalNormal += normals[k][i - 1][j - 1]; // upper left triangles

						if (i != 0 && j != m_cols - 1)
							finalNormal += normals[0][i - 1][j]; // upper right triangles

						if (i != m_rows - 1 && j != m_cols - 1)
							for (unsigned int k = 0; k < 2; k++) finalNormal += normals[k][i][j]; // bottom left triangles

						if (i != m_rows - 1 && j != 0)
							finalNormal += normals[0][i][j - 1]; // bottom left triangles

						m_normals[i][j] = glm::normalize(finalNormal);
					}
				}
			}

			void HeightMapFactory::FillHeightMapVBO(HeightMap* heightMap)
			{
				heightMap->m_vbo->Create(m_rows * m_cols * (2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
				for (unsigned int i = 0; i < m_rows; i++)
				{
					for (unsigned int j = 0; j < m_cols; j++)
					{
						heightMap->m_vbo->AddData(&m_vertexData[i][j], sizeof(glm::vec3));
						heightMap->m_vbo->AddData(&m_textureCoordsData[i][j], sizeof(glm::vec2));
						heightMap->m_vbo->AddData(&m_normals[i][j], sizeof(glm::vec3));
					}
				}
			}

			void HeightMapFactory::FillHeightMapIndicesVBO(HeightMap* heightMap)
			{
				int primitiveRestartIndex = m_rows * m_cols;

				heightMap->m_vboIndices->Create();
				for (unsigned int i = 0; i < m_rows - 1; i++)
				{
					for (unsigned int j = 0; j < m_cols - 1; j++)
					{
						for (unsigned int k = 0; k < 2; k++)
						{
							int row = i + (1 - k);
							int index = row * m_cols + j;
							heightMap->m_vboIndices->AddData(&index, sizeof(int));
						}
					}

					heightMap->m_vboIndices->AddData(&primitiveRestartIndex, sizeof(int));
				}
			}

			void HeightMapFactory::BindHeightMapData(HeightMap* heightMap)
			{
				glGenVertexArrays(1, &(heightMap->m_vertexAttributeObject));
				glBindVertexArray(heightMap->m_vertexAttributeObject);

				heightMap->m_vbo->Bind();
				heightMap->m_vbo->UploadDataToGPU(GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

				// indices
				heightMap->m_vboIndices->Bind(GL_ELEMENT_ARRAY_BUFFER);
				heightMap->m_vboIndices->UploadDataToGPU(GL_STATIC_DRAW);

				glBindVertexArray(0);
			}

			void HeightMapFactory::InvalidateState()
			{
				m_pixelStep = 0;
				m_pixelRowStep = 0;
				m_rows = 0;
				m_cols = 0;
				m_vertexData.clear();
				m_textureCoordsData.clear();
				m_normals.clear();
			}

			HeightMap* HeightMapFactory::GetHeightMapCommon(const std::string textureFilePath)
			{
				FIBITMAP* dib = GetImage(textureFilePath);

				HeightMap* heightMap = new HeightMap();

				unsigned char* data = FreeImage_GetBits(dib);

				if (data == NULL || FreeImage_GetHeight(dib) == 0 || FreeImage_GetWidth(dib) == 0 || (FreeImage_GetBPP(dib) != 24 && FreeImage_GetBPP(dib) != 8))
					throw HeightMapException("HeightMap " + textureFilePath + " is invalid.");

				heightMap->m_rows = m_rows = FreeImage_GetHeight(dib);
				heightMap->m_cols = m_cols = FreeImage_GetWidth(dib);

				m_pixelStep = FreeImage_GetBPP(dib) == 24 ? 3 : 1;
				m_pixelRowStep = m_pixelStep * heightMap->m_cols;

				ReadImageData(data);
				GenerateNormals();
				FillHeightMapVBO(heightMap);
				FillHeightMapIndicesVBO(heightMap);
				BindHeightMapData(heightMap);
				heightMap->m_vertexData = m_vertexData;
				heightMap->m_isLoaded = true;
				return heightMap;
			}

			IHeightMap* HeightMapFactory::CreateHeightMap(const std::string& textureFilePath)
			{
				HeightMap* heightMap = GetHeightMapCommon(textureFilePath);
				heightMap->m_hasGrass = false;
				InvalidateState();
				return heightMap;
			}
		}
	}
}