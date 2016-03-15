#include "File.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			bool File::Exists(const std::string& filePath)
			{
				FileReader fileReader;
				return fileReader.Open(filePath);
			}

			void File::CreateDirectoryByPath(const std::string& path)
			{
#ifdef _WIN32
				CreateDirectoryA(path.c_str(), NULL);
#else
				mkdir(path.c_str()); // TODO
#endif
			}

			std::string File::GetDirectoryPath(const std::string& filePath)
			{
				std::string result;
				for (size_t i = filePath.size() - 1; i > 0; i--)
				{
					if (filePath[i] == '\\' || filePath[i] == '//' || filePath[i] == '/')
					{
						result = filePath.substr(0, i + 1);
						break;
					}
				}
				return result;
			}
		}
	}
}