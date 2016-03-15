#include "FileReader.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			FileReader::FileReader()
			{
			}

			FileReader::FileReader(const char* filePath, std::ios::openmode mode)
				: m_filePath(filePath)
			{
				Open(filePath, mode);
			}

			FileReader::FileReader(std::string filePath, std::ios::openmode mode)
				: m_filePath(filePath)
			{
				Open(filePath, mode);
			}

			FileReader::~FileReader()
			{
				if (m_fileStream.is_open())
				{
					m_fileStream.close();
				}
			}

			bool FileReader::IsOpen() const
			{
				return m_fileStream.is_open();
			}

			bool FileReader::Open(std::string filePath, std::ios::openmode mode)
			{
				return Open(filePath.c_str(), mode);
			}

			bool FileReader::Open(const char* filePath, std::ios::openmode mode)
			{
				m_filePath = filePath;
				m_fileStream.open(filePath, mode);
				bool isOpen = IsOpen();
				if (isOpen)
				{
					std::streamoff pos = m_fileStream.tellg();
					m_fileStream.seekg(0, std::ios::end);
					m_fileLength = m_fileStream.tellg();
					// Restore the position of the get pointer
					m_fileStream.seekg(pos);
				}
				else
				{
					m_fileLength = 0;
				}
				return isOpen;
			}

			void FileReader::Close()
			{
				m_fileStream.close();
			}

			bool FileReader::IsEOF() const
			{
				return m_fileStream.eof();
			}

			std::string FileReader::ReadLine()
			{
				std::string line;
				std::getline(m_fileStream, line);
				return line;
			}

			std::string FileReader::ReadAllLines()
			{
				std::string line;
				std::stringstream contentStream;
				while (!m_fileStream.eof())
				{
					std::getline(m_fileStream, line);
					contentStream << line;
					contentStream << '\n';
				}
				return contentStream.str();
			}

			unsigned char FileReader::ReadUnsignedChar()
			{
				unsigned char result = 0;

				result = m_fileStream.get();
				return result;
			}

			char FileReader::ReadChar()
			{
				char result = 0;

				result = m_fileStream.get();
				return result;
			}

			void FileReader::ReadBytes(uint8_t* byteArray, unsigned int length)
			{
				m_fileStream.read(reinterpret_cast<char*>(byteArray), length);
			}

			void FileReader::ReadBytes(char* byteArray, unsigned int length)
			{
				m_fileStream.read(byteArray, length);
			}

			void FileReader::Ignore(unsigned int bytesCountToIgnore)
			{
				m_fileStream.ignore(bytesCountToIgnore);
			}

			void FileReader::IgnoreLine()
			{
				m_fileStream.ignore(m_fileLength, '\n');
			}

			long long FileReader::GetFileLength() const
			{
				return m_fileLength;
			}

			short FileReader::ReadShort() 
			{
				int result = 0;
				unsigned char inputChar = 0;

				inputChar = m_fileStream.get();
				result = inputChar;
				inputChar = m_fileStream.get();
				result |= ((unsigned int)inputChar << 8);
				return result;
			}

			int FileReader::ReadInt() 
			{
				int result = 0;
				unsigned char inputChar = 0;

				inputChar = m_fileStream.get();
				result = inputChar;
				inputChar = m_fileStream.get();
				result |= ((unsigned int)inputChar << 8);
				inputChar = m_fileStream.get();
				result |= ((unsigned int)inputChar << 16);
				inputChar = m_fileStream.get();
				result |= ((unsigned int)inputChar << 24);
				return result;
			}

			long FileReader::ReadLong()
			{
				long result = 0;
				unsigned char inputChar = 0;

				inputChar = m_fileStream.get();
				result = inputChar;
				inputChar = m_fileStream.get();
				result |= ((unsigned long)inputChar << 8);
				inputChar = m_fileStream.get();
				result |= ((unsigned long)inputChar << 16);
				inputChar = m_fileStream.get();
				result |= ((unsigned long)inputChar << 24);
				return result;
			}


			std::string FileReader::GetFilePath() const
			{
				return m_filePath;
			}

			std::string FileReader::GetDirectoryPath() const
			{
				std::string result;
				for (size_t i = m_filePath.size() - 1; i > 0; i--)
				{
					if (m_filePath[i] == '\\' || m_filePath[i] == '//' || m_filePath[i] == '/')
					{
						result = m_filePath.substr(0, i + 1);
						break;
					}
				}
				return result;
			}

			std::ifstream& FileReader::GetStream()
			{
				return m_fileStream;
			}
		}
	}
}