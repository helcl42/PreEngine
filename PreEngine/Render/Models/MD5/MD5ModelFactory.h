#ifndef MD5_MODEL_FACTORY_H
#define MD5_MODEL_FACTORY_H

#include "../../../Core/Common.h"
#include "../../Textures/TextureFactory.h"
#include "MD5Model.h"
#include "../AbstractModelFactory.h"
#include "IMD5ModelFactory.h"
#include "../../../Utils/IO/File.h"
#include "../../../Utils/Render/RenderUtil.h"

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			enum VB_TYPES
			{
				INDEX_BUFFER = 0,
				POS_VB,
				NORMAL_VB,
				TEXCOORD_VB,
				BONE_VB,
				NUM_VBs
			};

			namespace MD5
			{
				using namespace PreEngine::Utils;
				using namespace PreEngine::Utils::Render;
				using namespace PreEngine::Utils::IO;

				class MD5ModelFactory : public AbstractModelFactory, public IMD5ModelFactory
				{
				private:
					/*void ReadSingleFace(const aiMesh* mesh, const aiFace& face, MD5Model* model);

					void ReadSingleFaceIndices(const aiMesh* mesh, const aiFace& face, MD5Model* model);

					void ReadSingleMesh(const aiMesh* mesh, MD5Model* model);

					void ReadMeshes(const aiScene* scene, MD5Model* model, std::vector<VertexBoneData>& Bones);

					void BindData(MD5Model* model);*/

				private:
					bool InitFromScene(const aiScene* pScene, MD5Model* model, const std::string& Filename);

					void InitMaterials(const aiScene* scene, MD5Model* model, std::string filePath);

					void InitMesh(MD5Model* model, unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<glm::vec3>& Positions, std::vector<glm::vec3>& Normals, std::vector<glm::vec2>& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices);
					
					void LoadBones(MD5Model* model, unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<VertexBoneData>& Bones);
					
					void BindData(MD5Model* model, std::vector<glm::vec3>& Positions, std::vector<glm::vec3>& Normals, std::vector<glm::vec2>& TexCoords, std::vector<VertexBoneData>& Bones, std::vector<unsigned int>& Indices);

				public:
					MD5ModelFactory();

					virtual ~MD5ModelFactory();

				public:
					MD5Model* CreateModel(const std::string& filePath);
				};
			}
		}
	}
}

#endif