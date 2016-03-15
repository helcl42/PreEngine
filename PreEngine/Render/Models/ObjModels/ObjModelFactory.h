#ifndef OBJ_MODEL_FACTORY_H
#define OBJ_MODEL_FACTORY_H

#include "../AbstractModelFactory.h"
#include "ObjModel.h"
#include "IObjModelFactory.h"
#include "../ModelException.h"
#include "../../Textures/TextureFactory.h"
#include "../../../Utils/StringUtils.h"
#include "../../../Utils/IO/FileReader.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace ObjModels
			{
				using namespace Utils::IO;

				class ObjModelFactory : public AbstractModelFactory, public IObjModelFactory
				{
				private:
					unsigned int m_countOfFaces;

					int m_attrBitField;

					glm::vec3 m_lowerLeftFront;

					glm::vec3 m_upperRightBack;

					std::vector<glm::vec3> m_vertices;

					std::vector<glm::vec2> m_textureCoords;

					std::vector<glm::vec3> m_normals;

					IFileReader* m_fileReader;

				public:
					ObjModelFactory();

					virtual ~ObjModelFactory();

				private:
					void Reset();

					ITexture* LoadMaterial(std::string mtlFilePath);

					void ReadSingleVetexGroup(std::stringstream& ss);

					void ReadSingleTextureCoordinate(std::stringstream& ss);

					void ReadSingleNormal(std::stringstream& ss);

					void ReadSingleFace(ObjModel* objModel, std::stringstream& ss);

					void ReadSingleModelLine(ObjModel* objModel, std::string line);

					void BindData(ObjModel* objModel);

					void BindBoundingBoxData(ObjModel* objModel);

					void Center();

				public:
					IModel* CreateModel(const std::string& filePath, const std::string& mtlFilPath);
				};
			}
		}
	}
}

#endif 