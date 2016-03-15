#include "AssimpModel.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Assimp
			{
				AssimpModel::AssimpModel()
					: m_isLoaded(false), m_hasBumpMap(false), m_defaultTexturesEnabled(true), m_countOfMaterials(0), m_vertexAttributeObject(0), m_countOfFaces(0)
				{
					m_vbo = new VertexBufferObject();
					m_vboBumpMap = new VertexBufferObject();
					m_vboIndices = new VertexBufferObject();
				}

				AssimpModel::~AssimpModel()
				{
					SAFE_DELETE(m_vboIndices);
					SAFE_DELETE(m_vboBumpMap);
					SAFE_DELETE(m_vbo);
				}

				void AssimpModel::Init()
				{
				}

				void AssimpModel::Render(GLenum how)
				{
					if (!m_isLoaded) throw new ModelException("Could not render not loaded model.");

					glBindVertexArray(m_vertexAttributeObject);
					for (unsigned int i = 0; i < m_meshSizes.size(); i++)
					{
						unsigned int materialIndex = (unsigned int)(m_materialIndices[i]);
						if (m_textures.size() > materialIndex && m_defaultTexturesEnabled) m_textures[materialIndex]->Bind(0);
						if (m_hasBumpMap) m_normalTexrure->Bind(1);
						//if (m_renderWithAdjacents) // TODO
						//{
						//	glDrawElements(GL_TRIANGLES_ADJACENCY, m_meshSizes[i], GL_UNSIGNED_INT, NULL);
						//}
						//else
						//{
							glDrawArrays(how, m_meshStartIndices[i], m_meshSizes[i]);	
						//}
					}
				}

				void AssimpModel::RenderBoundingBox()
				{
				}

				void AssimpModel::Delete()
				{
					if (!m_isLoaded) throw new ModelException("Could not release not loaded model.");

					for (std::vector<ITexture*>::iterator ii = m_textures.begin(); ii != m_textures.end(); ii++)
					{
						(*ii)->Delete();
						SAFE_DELETE(*ii);
					}

					if (m_hasBumpMap && m_normalTexrure != NULL)
					{
						m_normalTexrure->Delete();
						SAFE_DELETE(m_normalTexrure);
					}

					m_vbo->Delete();
					m_vboIndices->Delete();
					m_vboBumpMap->Delete();

					glDeleteVertexArrays(1, &m_vertexAttributeObject);
					m_vertexAttributeObject = 0;
					m_isLoaded = false;
				}

				bool AssimpModel::IsLoaded() const
				{
					return m_isLoaded;
				}

				unsigned int AssimpModel::GetPolygonCount() const
				{
					return m_countOfFaces;
				}

				void  AssimpModel::SetDefaultTexturesEnabled(bool enabled)
				{
					m_defaultTexturesEnabled = enabled;
				}

				bool AssimpModel::IsDefaultTexturesEnabled() const
				{
					return m_defaultTexturesEnabled;
				}
			}
		}
	}
}