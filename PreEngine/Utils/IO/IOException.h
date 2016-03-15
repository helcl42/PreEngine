#ifndef IO_EXCEPTION_H
#define IO_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace IO
		{
			class IOException : public std::runtime_error
			{
			public:
				IOException(const std::string& msg)
					: std::runtime_error(msg)
				{
				}
			};
		}
	}
}

#endif