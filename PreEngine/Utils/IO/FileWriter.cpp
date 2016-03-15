#include "FileWriter.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			FileWriter::FileWriter()
			{
			}

			FileWriter::FileWriter(const char* filePath)
				: m_filePath(filePath)
			{
				Open(filePath);
			}

			FileWriter::~FileWriter()
			{
				if (m_fileStream.is_open())
				{
					m_fileStream.close();
				}
			}

			bool FileWriter::IsOpen() const
			{
				return m_fileStream.is_open();
			}

			bool FileWriter::Open(std::string path, std::ios::openmode mode)
			{
				return Open(path.c_str(), mode);
			}

			bool FileWriter::Open(const char* filePath, std::ios::openmode mode)
			{
				m_filePath = filePath;
				m_fileStream.open(filePath, mode);
				return IsOpen();
			}

			void FileWriter::Close()
			{
				m_fileStream.close();
			}

			void FileWriter::Write(const std::string& line)
			{
				m_fileStream << line;
			}

			void FileWriter::WriteNewLine()
			{
				m_fileStream << std::endl;
			}

			void FileWriter::WriteLine(const std::string& line)
			{
				Write(line);
				WriteNewLine();
			}

			void FileWriter::Write(char byte)
			{
				m_fileStream.put((unsigned char)byte);
			}

			void FileWriter::WriteShort(short value) 
			{
				m_fileStream.put((unsigned char)value);
				m_fileStream.put((unsigned char)(value >> 8));
			}

			void FileWriter::WriteInt(int value)
			{
				m_fileStream.put((unsigned char)value);
				m_fileStream.put((unsigned char)(value >> 8));
				m_fileStream.put((unsigned char)(value >> 16));
				m_fileStream.put((unsigned char)(value >> 24));
			}

			void FileWriter::WriteBytes(char* values, unsigned int lenght)
			{
				m_fileStream.write(values, lenght);
			}

			void FileWriter::WriteBytes(uint8_t* values, unsigned int length)
			{
				m_fileStream.write(reinterpret_cast<char*>(values), length);
			}

			std::string FileWriter::GetFilePath() const
			{
				return m_filePath;
			}
		}
	}
}