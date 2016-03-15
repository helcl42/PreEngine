#ifndef IFILE_WRITER_H
#define IFILE_WRITER_H

#include <fstream>
#include <string>
#include <iostream>
#include <inttypes.h>

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class IFileWriter
			{
			public:
				virtual bool IsOpen() const = 0;

				virtual bool Open(const char* filePath, std::ios::openmode mode = std::ios::out) = 0;

				virtual bool Open(std::string filePath, std::ios::openmode mode = std::ios::out) = 0;

				virtual void Close() = 0;

				virtual void Write(const std::string& line) = 0;

				virtual void Write(char value) = 0;

				virtual void WriteNewLine() = 0;

				virtual void WriteLine(const std::string& line) = 0;

				virtual void WriteShort(short value) = 0;

				virtual void WriteInt(int value) = 0;

				virtual void WriteBytes(char* values, unsigned int lenght) = 0;

				virtual void WriteBytes(uint8_t* values, unsigned int lenght) = 0;

				virtual std::string GetFilePath() const = 0;

			public:
				virtual ~IFileWriter() {}
			};
		}
	}
}

#endif