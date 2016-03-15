#ifndef FILE_READER_H
#define FILE_READER_H

#include "IFileReader.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class FileReader : public IFileReader
			{
			private:
				std::string m_filePath;

				std::ifstream m_fileStream;

				long long m_fileLength;

			public:
				FileReader();

				FileReader(const char* filePath, std::ios::openmode mode = std::ios::in);

				FileReader(std::string filePath, std::ios::openmode mode = std::ios::in);

				virtual ~FileReader();

			public:
				bool IsOpen() const;

				bool Open(const char* filePath, std::ios::openmode mode = std::ios::in);

				bool Open(std::string filePath, std::ios::openmode mode = std::ios::in);

				bool IsEOF() const;

				void Close();

				std::string ReadLine();

				std::string ReadAllLines();

				char ReadChar();

				unsigned char ReadUnsignedChar();

				void ReadBytes(char* byteArray, unsigned int length);

				void ReadBytes(uint8_t* byteArray, unsigned int length);

				short ReadShort();

				int ReadInt();

				long ReadLong();

				void Ignore(unsigned int bytesCoutnToIgnore = 1);

				void IgnoreLine();

				long long GetFileLength() const;

				std::string GetFilePath() const;

				std::string GetDirectoryPath() const;

				std::ifstream& GetStream();
			};
		}
	}
}

#endif