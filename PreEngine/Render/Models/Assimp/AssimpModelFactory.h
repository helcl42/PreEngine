#ifndef ASSIMP_MODEL_FACTORY_H
#define ASSIMP_MODEL_FACTORY_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../../Core/Common.h"
#include "../../Textures/TextureFactory.h"
#include "AssimpModel.h"
#include "../AbstractModelFactory.h"
#include "IAssimpModelFactory.h"
#include "../../../Utils/IO/File.h"
#include "../../../Utils/Render/RenderUtil.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Assimp
			{
				using namespace PreEngine::Utils;
				using namespace PreEngine::Utils::Render;
				using namespace PreEngine::Utils::IO;

				class AssimpModelFactory : public AbstractModelFactory, public IAssimpModelFactory
				{
				private:
					void ReadSingleFace(const aiMesh* mesh, const aiFace& face, AssimpModel* assimpModel);

					void AddBumpMapData(const aiMesh* mesh, const aiFace& face, AssimpModel* assimpModel);

					//void PrepareAdjacentIndices(const aiScene* scene, AssimpModel* assimpModel);

					int ReadSingleMesh(const aiMesh* mesh, AssimpModel* assimpModel, bool useBumpMap);

					void ReadMeshes(const aiScene* scene, AssimpModel* assimpModel, bool useBumpMap);

					int GetTextureIndex(AssimpModel* assimpModel, const std::string& fullPath);

					void ReadMaterials(const aiScene* scene, AssimpModel* assimpModel, std::string filePath, std::string texturePath);

					void BindData(AssimpModel* assimpModel, bool hasBumpMap = false);

					bool SetNormalTexture(AssimpModel* assimpModel, std::string normalTexturePath);

					AssimpModel* CreateModelBase(std::string filePath, std::string texturePath, bool hasBumpMap = false);

				public:
					AssimpModelFactory();

					virtual ~AssimpModelFactory();

				public:
					IModel* CreateModel(std::string filePath);

					IModel* CreateModel(std::string filePath, std::string texturePath);

					IModel* CreateModel(std::string filePath, std::string texturePath, std::string normalTexturePath);
				};
			}
		}
	}
}

#endif