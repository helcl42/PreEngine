#include "ObjModel.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace ObjModels
			{
				ObjModel::ObjModel()
					: m_isLoaded(false), m_defaultTexturesEnabled(true), m_attrBitField(0), m_countOfFaces(0), m_vertexAttributeObject(0), m_vertexAttributeObjectBB(0)
				{
					m_vbo = new VertexBufferObject();
					m_vboBB = new VertexBufferObject();
					m_vboBBIndices = new VertexBufferObject();
				}

				ObjModel::~ObjModel()
				{
					SAFE_DELETE(m_ambientTexture);
					SAFE_DELETE(m_vboBBIndices);
					SAFE_DELETE(m_vboBB);
					SAFE_DELETE(m_vbo);
				}

				void ObjModel::Init()
				{
				}

				void ObjModel::Render(GLenum how)
				{
					if (!m_isLoaded) throw new ModelException("Could not render not loaded model.");
					glBindVertexArray(m_vertexAttributeObject);
					m_ambientTexture->Bind();
					glDrawArrays(how, 0, m_countOfFaces * 3);
				}

				void ObjModel::RenderBoundingBox()
				{
					if (!m_isLoaded) throw new ModelException("Could not render bounding box of not loaded model.");
					glBindVertexArray(m_vertexAttributeObjectBB);

					glEnable(GL_PRIMITIVE_RESTART);
					glPrimitiveRestartIndex(8);
					glDrawElements(GL_TRIANGLE_STRIP, 29, GL_UNSIGNED_INT, 0);
				}

				void ObjModel::Delete()
				{
					if (!m_isLoaded) throw new ModelException("Could not release not loaded model.");
					if (m_defaultTexturesEnabled) m_ambientTexture->Delete();
					glDeleteVertexArrays(1, &m_vertexAttributeObjectBB);
					glDeleteVertexArrays(1, &m_vertexAttributeObject);
					m_vboBBIndices->Delete();
					m_vboBB->Delete();
					m_vbo->Delete();
					m_isLoaded = false;
				}

				void  ObjModel::SetDefaultTexturesEnabled(bool enabled)
				{
					m_defaultTexturesEnabled = enabled;
				}

				bool ObjModel::IsDefaultTexturesEnabled() const
				{
					return m_defaultTexturesEnabled;
				}

				bool ObjModel::IsLoaded() const
				{
					return m_isLoaded;
				}

				unsigned int ObjModel::GetPolygonCount() const
				{
					return m_countOfFaces;
				}
			}
		}
	}
}