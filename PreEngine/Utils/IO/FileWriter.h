#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include "IFileWriter.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class FileWriter : public IFileWriter
			{
			private:
				std::string m_filePath;

				std::ofstream m_fileStream;

			public:
				FileWriter();

				FileWriter(const char* filePath);

				virtual ~FileWriter();

			public:
				bool IsOpen() const;

				bool Open(const char* filePath, std::ios::openmode mode = std::ios::out);

				bool Open(std::string filePath, std::ios::openmode mode = std::ios::out);

				void Close();

				void Write(const std::string& line);

				void Write(char byte);

				void WriteNewLine();

				void WriteLine(const std::string& line);

				void WriteShort(short value);

				void WriteInt(int value);

				void WriteBytes(char* values, unsigned int lenght);

				void WriteBytes(uint8_t* values, unsigned int lenght);

				std::string GetFilePath() const;
			};
		};
	}
}

#endif 