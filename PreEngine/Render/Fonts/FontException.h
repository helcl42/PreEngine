#ifndef FONT_EXCEPTION_H
#define FONT_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			using namespace Utils::Log;

			class FontException : public std::runtime_error
			{
			public:
				FontException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~FontException()
				{
				}
			};
		}
	}
}

#endif
