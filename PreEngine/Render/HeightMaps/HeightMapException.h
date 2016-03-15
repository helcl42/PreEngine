#ifndef HEIGHT_MAP_EXCEPTION_H
#define HEIGHT_MAP_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace HeightMaps
		{
			using namespace Utils::Log;

			class HeightMapException : public std::runtime_error
			{
			public:
				HeightMapException(const std::string& message)
					: std::runtime_error(message)
				{
					Logger::GetInstance().Error() << message;
				}

				virtual ~HeightMapException()
				{
				}
			};
		}
	}
}

#endif