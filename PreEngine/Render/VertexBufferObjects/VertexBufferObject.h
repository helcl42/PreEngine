#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include "../../Core/Common.h"
#include "IVertexBufferObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace VertexBufferObjects
		{
			class VertexBufferObject : public IVertexBufferObject
			{
			private:
				unsigned int m_handle;

				unsigned int m_size;

				unsigned int m_currentSize;

				GLenum m_bufferType;

				std::vector<GLubyte> m_data;

				bool m_dataUploaded;

			public:
				VertexBufferObject();

				virtual ~VertexBufferObject();

			public:
				void Create(unsigned int size = 0);

				void Delete();

				void* MapBufferToMemory(GLenum usageHint);

				void* MapSubBufferToMemory(GLenum usageHint, unsigned int offset, unsigned int length);

				void UnmapBuffer();

				void Bind(GLenum bufferType = GL_ARRAY_BUFFER);

				void UploadDataToGPU(GLenum usageHint);

				void AddData(void* data, unsigned int size);

				GLubyte* GetData() const;

				int GetCurrentSize() const;

				unsigned int GetHandle() const;
			};
		}
	}
}

#endif