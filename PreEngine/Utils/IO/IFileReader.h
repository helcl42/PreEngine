#ifndef IFILE_READER_H
#define IFILE_READER_H

#include <fstream>
#include <string>
#include <iostream>

#include "IOException.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class IFileReader
			{
			public:
				virtual bool IsOpen() const = 0;

				virtual bool Open(const char* filePath, std::ios::openmode mode = std::ios::in) = 0;

				virtual bool Open(std::string filePath, std::ios::openmode mode = std::ios::in) = 0;

				virtual void Close() = 0;

				virtual bool IsEOF() const = 0;

				virtual std::string ReadLine() = 0;

				virtual std::string ReadAllLines() = 0;

				virtual char ReadChar() = 0;

				virtual unsigned char ReadUnsignedChar() = 0;

				virtual void ReadBytes(char* byteArray, unsigned int length) = 0;

				virtual void ReadBytes(uint8_t* byteArray, unsigned int length) = 0;

				virtual short ReadShort() = 0;

				virtual int ReadInt() = 0;

				virtual long ReadLong() = 0;

				virtual void Ignore(unsigned int bytesCountToIgnore) = 0;

				virtual void IgnoreLine() = 0;

				virtual long long GetFileLength() const = 0;

				virtual std::string GetFilePath() const = 0;

				virtual std::string GetDirectoryPath() const = 0;

				virtual std::ifstream& GetStream() = 0;

			public:
				virtual ~IFileReader() {}
			};
		}
	}
}

#endif