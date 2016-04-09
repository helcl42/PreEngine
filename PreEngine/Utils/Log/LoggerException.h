#ifndef LOGGER_EXCEPTION_H
#define LOGGER_EXCEPTION_H

namespace PreEngine
{
	namespace Utils
	{
		namespace Log
		{
			class LoggerException : public std::runtime_error
			{
			public:
				LoggerException(const std::string& message)
					: std::runtime_error(message)
				{
				}

				virtual ~LoggerException()
				{
				}
			};
		}
	}
}


#endif