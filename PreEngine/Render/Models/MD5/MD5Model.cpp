#include "MD5Model.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				MD5Model::MD5Model()
					: m_isLoaded(false), m_defaultTexturesEnabled(true), m_countOfMaterials(0), m_vertexAttributeObject(0), m_countOfFaces(0)
				{
				}

				MD5Model::~MD5Model()
				{
					for (std::vector<ITexture*>::iterator ii = m_textures.begin(); ii != m_textures.end(); ii++)
					{
						SAFE_DELETE(*ii);
					}
				}

				void MD5Model::Init()
				{
				}

				unsigned int MD5Model::FindPosition(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					for (unsigned int i = 0; i < nodeAnimation->mNumPositionKeys - 1; i++)
					{
						if (animationTime < (float)nodeAnimation->mPositionKeys[i + 1].mTime)
						{
							return i;
						}
					}
					assert(0);
					return 0;
				}


				unsigned int MD5Model::FindRotation(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					assert(nodeAnimation->mNumRotationKeys > 0);
					for (unsigned int i = 0; i < nodeAnimation->mNumRotationKeys - 1; i++)
					{
						if (animationTime < (float)nodeAnimation->mRotationKeys[i + 1].mTime)
						{
							return i;
						}
					}
					assert(0);
					return 0;
				}


				unsigned int MD5Model::FindScaling(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					assert(nodeAnimation->mNumScalingKeys > 0);
					for (unsigned int i = 0; i < nodeAnimation->mNumScalingKeys - 1; i++)
					{
						if (animationTime < (float)nodeAnimation->mScalingKeys[i + 1].mTime)
						{
							return i;
						}
					}
					assert(0);
					return 0;
				}

				const aiNodeAnim* MD5Model::FindNodeAnim(const aiAnimation* animation, const std::string nodeName)
				{
					for (unsigned int i = 0; i < animation->mNumChannels; i++)
					{
						const aiNodeAnim* nodeAnimation = animation->mChannels[i];
						if (std::string(nodeAnimation->mNodeName.data) == nodeName)
						{
							return nodeAnimation;
						}
					}
					return NULL;
				}

				aiVector3D MD5Model::CalcInterpolatedPosition(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					aiVector3D outVector;
					if (nodeAnimation->mNumPositionKeys == 1)
					{
						outVector = nodeAnimation->mPositionKeys[0].mValue;
					}
					else
					{
						unsigned int positionIndex = FindPosition(animationTime, nodeAnimation);
						unsigned int nextPositionIndex = (positionIndex + 1);
						assert(nextPositionIndex < nodeAnimation->mNumPositionKeys);
						float deltaTime = (float)(nodeAnimation->mPositionKeys[nextPositionIndex].mTime - nodeAnimation->mPositionKeys[positionIndex].mTime);
						float factor = (animationTime - (float)nodeAnimation->mPositionKeys[positionIndex].mTime) / deltaTime;
						assert(factor >= 0.0f && factor <= 1.0f);
						const aiVector3D& start = nodeAnimation->mPositionKeys[positionIndex].mValue;
						const aiVector3D& end = nodeAnimation->mPositionKeys[nextPositionIndex].mValue;
						aiVector3D delta = end - start;
						outVector = start + factor * delta;
					}
					return outVector;
				}

				aiQuaternion MD5Model::CalcInterpolatedRotation(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					aiQuaternion outQuanternion;
					if (nodeAnimation->mNumRotationKeys == 1)
					{
						outQuanternion = nodeAnimation->mRotationKeys[0].mValue;
					}
					else
					{
						unsigned int RotationIndex = FindRotation(animationTime, nodeAnimation);
						unsigned int NextRotationIndex = (RotationIndex + 1);
						assert(NextRotationIndex < nodeAnimation->mNumRotationKeys);
						float deltaTime = (float)(nodeAnimation->mRotationKeys[NextRotationIndex].mTime - nodeAnimation->mRotationKeys[RotationIndex].mTime);
						float factor = (animationTime - (float)nodeAnimation->mRotationKeys[RotationIndex].mTime) / deltaTime;
						assert(factor >= 0.0f && factor <= 1.0f);
						const aiQuaternion& startRotationQ = nodeAnimation->mRotationKeys[RotationIndex].mValue;
						const aiQuaternion& endRotationQ = nodeAnimation->mRotationKeys[NextRotationIndex].mValue;
						aiQuaternion::Interpolate(outQuanternion, startRotationQ, endRotationQ, factor);
						outQuanternion = outQuanternion.Normalize();
					}
					return outQuanternion;
				}

				aiVector3D MD5Model::CalcInterpolatedScaling(float animationTime, const aiNodeAnim* nodeAnimation)
				{
					aiVector3D outVector;
					if (nodeAnimation->mNumScalingKeys == 1)
					{
						outVector = nodeAnimation->mScalingKeys[0].mValue;
					}
					else
					{
						unsigned int ScalingIndex = FindScaling(animationTime, nodeAnimation);
						unsigned int NextScalingIndex = (ScalingIndex + 1);
						assert(NextScalingIndex < nodeAnimation->mNumScalingKeys);
						float deltaTime = (float)(nodeAnimation->mScalingKeys[NextScalingIndex].mTime - nodeAnimation->mScalingKeys[ScalingIndex].mTime);
						float factor = (animationTime - (float)nodeAnimation->mScalingKeys[ScalingIndex].mTime) / deltaTime;
						assert(factor >= 0.0f && factor <= 1.0f);
						const aiVector3D& start = nodeAnimation->mScalingKeys[ScalingIndex].mValue;
						const aiVector3D& end = nodeAnimation->mScalingKeys[NextScalingIndex].mValue;
						aiVector3D delta = end - start;
						outVector = start + factor * delta;
					}
					return outVector;
				}

				void MD5Model::ReadNodeHeirarchy(float animationTime, const aiNode* node, const glm::mat4& parentTransformation)
				{
					std::string nodeName(node->mName.data);
					const aiAnimation* animation = m_scene->mAnimations[0];
					glm::mat4 nodeTransformation = AIToGLMUtil::Mat4(node->mTransformation);
					const aiNodeAnim* nodeAnimation = FindNodeAnim(animation, nodeName);

					if (nodeAnimation)
					{
						aiVector3D scaling = CalcInterpolatedScaling(animationTime, nodeAnimation);
						glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), glm::vec3(scaling.x, scaling.y, scaling.z));

						aiQuaternion rotationQ = CalcInterpolatedRotation(animationTime, nodeAnimation);
						glm::mat4 rotationMatrix = AIToGLMUtil::Mat4(rotationQ.GetMatrix());

						aiVector3D translation = CalcInterpolatedPosition(animationTime, nodeAnimation);
						glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), glm::vec3(translation.x, translation.y, translation.z));

						nodeTransformation = translationMatrix * rotationMatrix * scaleMatrix;
					}

					glm::mat4 globalTransformation = parentTransformation * nodeTransformation;
					if (m_boneMapping.find(nodeName) != m_boneMapping.end())
					{
						unsigned int boneIndex = m_boneMapping[nodeName];
						m_boneInfos[boneIndex].finalTransformation = m_globalInverseTransform * globalTransformation * m_boneInfos[boneIndex].boneOffset;
					}

					for (unsigned int i = 0; i < node->mNumChildren; i++)
					{
						ReadNodeHeirarchy(animationTime, node->mChildren[i], globalTransformation);
					}
				}

				void MD5Model::Update(float deltaTime)
				{
					m_elapsedTime += deltaTime;
					glm::mat4 identityMatrix(1.0);

					float ticksPerSecond = (float)(m_scene->mAnimations[0]->mTicksPerSecond != 0 ? m_scene->mAnimations[0]->mTicksPerSecond : 25.0f);
					float timeInTicks = m_elapsedTime * ticksPerSecond;
					float animationTime = fmod(timeInTicks, (float)m_scene->mAnimations[0]->mDuration);

					ReadNodeHeirarchy(animationTime, m_scene->mRootNode, identityMatrix);

					m_previousBoneTransforms = m_boneTransforms;

					m_boneTransforms.resize(m_numBones);

					for (unsigned int i = 0; i < m_numBones; i++)
					{
						m_boneTransforms[i] = m_boneInfos[i].finalTransformation;
					}
				}

				void MD5Model::Render(GLenum how)
				{
					if (!m_isLoaded) throw ModelException("Could not render not loaded model.");

					glBindVertexArray(m_vertexAttributeObject);

					for (unsigned int i = 0; i < m_meshEntries.size(); i++)
					{
						const unsigned MaterialIndex = m_meshEntries[i].materialIndex;
						assert(MaterialIndex < m_textures.size());
						m_textures[MaterialIndex]->Bind();

						glDrawElementsBaseVertex(GL_TRIANGLES, m_meshEntries[i].numberOfIndices, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * m_meshEntries[i].baseIndex), m_meshEntries[i].baseVertex);
					}

					glBindVertexArray(0); // Make sure the VAO is not changed from the outside  
				}

				const std::vector<glm::mat4>& MD5Model::GetBoneTransforms() const
				{
					return m_boneTransforms;
				}

				const std::vector<glm::mat4>& MD5Model::GetPreviousBoneTransforms() const
				{
					return m_previousBoneTransforms;
				}

				void MD5Model::RenderBoundingBox()
				{
				}

				void MD5Model::Delete()
				{
					if (!m_isLoaded) throw ModelException("Could not release not loaded model.");

					for (std::vector<ITexture*>::iterator ii = m_textures.begin(); ii != m_textures.end(); ii++)
					{
						(*ii)->Delete();
					}

					glDeleteVertexArrays(1, &m_vertexAttributeObject);
					m_vertexAttributeObject = 0;
					m_isLoaded = false;
				}

				bool MD5Model::IsLoaded() const
				{
					return m_isLoaded;
				}

				unsigned int MD5Model::GetPolygonCount() const
				{
					return m_countOfFaces;
				}

				void  MD5Model::SetDefaultTexturesEnabled(bool enabled)
				{
					m_defaultTexturesEnabled = enabled;
				}

				bool MD5Model::IsDefaultTexturesEnabled() const
				{
					return m_defaultTexturesEnabled;
				}
			}
		}
	}
}