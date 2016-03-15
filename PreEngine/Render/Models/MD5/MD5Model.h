#ifndef MD5_MODEL_H
#define MD5_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../../Core/Common.h"
#include "../ModelException.h"
#include "../IModel.h"
#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Textures/Texture.h"

#include "AIToGLMUtil.h"
#include "MeshEntry.h"
#include "BoneInfo.h"
#include "VertexBoneData.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				using namespace PreEngine::Render::VertexBufferObjects;
				using namespace PreEngine::Render::Textures;

				class MD5Model : public IModel
				{
				private:
					friend class MD5ModelFactory;

				private:
					bool m_defaultTexturesEnabled;

					bool m_isLoaded;

					float m_elapsedTime;

					GLuint m_vertexAttributeObject;

					unsigned int m_countOfFaces;

					int m_countOfMaterials;

					std::vector<ITexture*> m_textures;
				
					std::vector<MeshEntry> m_meshEntries;

					std::map<std::string, unsigned int> m_boneMapping; // maps a bone name to its index

					unsigned int m_numBones;

					std::vector<BoneInfo> m_boneInfos;

					glm::mat4 m_globalInverseTransform;

					std::vector<glm::mat4> m_boneTransforms;

					std::vector<glm::mat4> m_previousBoneTransforms;

					const aiScene* m_scene;

					::Assimp::Importer importer;

				public:
					MD5Model();

					virtual ~MD5Model();

				private:
					unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

					unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

					unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

					aiVector3D CalcInterpolatedPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);

					aiQuaternion CalcInterpolatedRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
				
					aiVector3D CalcInterpolatedScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
					
					const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);

					void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform);

				public:				
					void Init();

					void Update(float deltaTime);

					void Render(GLenum how = GL_TRIANGLES);

					void RenderBoundingBox();

					void Delete();

					bool IsLoaded() const;

					void SetDefaultTexturesEnabled(bool enabled);

					bool IsDefaultTexturesEnabled() const;

					unsigned int GetPolygonCount() const;

					const std::vector<glm::mat4>& GetBoneTransforms() const;

					const std::vector<glm::mat4>& GetPreviousBoneTransforms() const;

				};
			}
		}
	}
}

#endif