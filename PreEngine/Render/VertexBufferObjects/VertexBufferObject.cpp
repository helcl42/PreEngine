#include "VertexBufferObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace VertexBufferObjects
		{
			VertexBufferObject::VertexBufferObject()
				: m_handle(0), m_size(0), m_dataUploaded(false)
			{
			}

			VertexBufferObject::~VertexBufferObject()
			{
			}

			void VertexBufferObject::Create(int unsigned size)
			{
				glGenBuffers(1, &m_handle);
				m_data.reserve(size);
				m_size = size;
				m_currentSize = 0;
			}

			void VertexBufferObject::Delete()
			{
				glDeleteBuffers(1, &m_handle);
				m_dataUploaded = false;
				m_data.clear();
				m_size = 0;
				m_currentSize = 0;
			}

			void* VertexBufferObject::MapBufferToMemory(GLenum usageHint)
			{
				if (m_dataUploaded) return NULL;
				void* res = glMapBuffer(m_bufferType, usageHint);
				return res;
			}

			void* VertexBufferObject::MapSubBufferToMemory(GLenum usageHint, unsigned int offset, unsigned int length)
			{
				if (m_dataUploaded) return NULL;
				void* res = glMapBufferRange(m_bufferType, offset, length, usageHint);
				return res;
			}

			void VertexBufferObject::UnmapBuffer()
			{
				glUnmapBuffer(m_handle);
			}

			void VertexBufferObject::Bind(GLenum bufferType)
			{
				m_bufferType = bufferType;
				glBindBuffer(m_bufferType, m_handle);
			}

			void VertexBufferObject::UploadDataToGPU(GLenum usageHint)
			{
				glBufferData(m_bufferType, m_data.size(), &m_data[0], usageHint);
				m_dataUploaded = true;
				m_data.clear();
				m_size = 0;
				m_currentSize = 0;
			}

			void VertexBufferObject::AddData(void* data, unsigned int size)
			{
				m_data.insert(m_data.end(), (GLubyte*)data, (GLubyte*)data + size);
				m_currentSize += size;
			}

			GLubyte* VertexBufferObject::GetData() const
			{
				if (m_dataUploaded) return NULL;
				return (GLubyte*)&m_data[0];
			}

			int VertexBufferObject::GetCurrentSize() const
			{
				return m_currentSize;
			}

			unsigned int VertexBufferObject::GetHandle() const
			{
				return m_handle;
			}
		}
	}
}