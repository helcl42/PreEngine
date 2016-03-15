#ifndef IVERTEX_BUFFER_OBJECT_H
#define IVERTEX_BUFFER_OBJECT_H

namespace PreEngine
{
	namespace Render
	{
		namespace VertexBufferObjects
		{
			class IVertexBufferObject
			{
			public:
				virtual void Create(unsigned int size = 0) = 0;

				virtual void Delete() = 0;

				virtual void* MapBufferToMemory(GLenum usageHint) = 0;

				virtual void* MapSubBufferToMemory(GLenum usageHint, unsigned int offset, unsigned int length) = 0;

				virtual void UnmapBuffer() = 0;

				virtual void Bind(GLenum bufferType = GL_ARRAY_BUFFER) = 0;

				virtual void UploadDataToGPU(GLenum usageHint) = 0;

				virtual void AddData(void* data, unsigned int size) = 0;

				virtual GLubyte* GetData() const = 0;

				virtual int GetCurrentSize() const = 0;

				virtual unsigned int GetHandle() const = 0;

			public:
				virtual ~IVertexBufferObject() {}
			};
		}
	}
}

#endif