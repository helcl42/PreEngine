#ifndef FILE_H
#define FILE_H

#include "FileReader.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class File
			{
			public:
				static bool Exists(const std::string& filePath);

				static std::string GetDirectoryPath(const std::string& filePath);

				static void CreateDirectoryByPath(const std::string& path);
			};
		}
	}
}


#endif