#ifndef MODEL_EXCEPTION_H
#define MODEL_EXCEPTION_H

#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			using namespace Utils::Log;

			class ModelException : public std::runtime_error
			{
			public:
				ModelException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~ModelException()
				{
				}
			};
		}
	}
}

#endif