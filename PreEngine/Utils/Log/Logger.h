#ifndef LOGGER_H
#define LOGGER_H

#include "../../Core/Common.h"
#include "LoggerException.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Log
		{
			class Logger
			{
			private:
				friend struct LogHelper;

			private:
				static Logger s_instance;

				struct LogHelper;

				std::mutex m_mutex;

				std::ofstream m_outputFile;

			private:
				Logger(const Logger&);;

				Logger(Logger&&);

				Logger& operator=(const Logger&);

				Logger& operator=(Logger&&);

				Logger();

			public:
				static Logger& GetInstance();

				void SetOutputFileName(const std::string& filename);

				template <typename T>
				LogHelper operator << (const T& message) 
				{
					LogHelper helper = Info();
					helper << message;
					return helper;
				}

				LogHelper operator << (std::ostream& (*fn)(std::ostream& os)); //overloading this allows std::iomanip functions to operate on a Logger

				LogHelper Debug();		// [dbg]

				LogHelper Info();		// this is the default (empty prefix)

				LogHelper Warning();	// [WARN]

				LogHelper Error();		// [** ERROR **]

				LogHelper Fatal();		// [<=== FATAL ===>]

			private:
				void Flush(std::string message);

				struct LogHelper
				{
					std::ostringstream m_buffer;

					Logger* m_parent;

					LogHelper(Logger* parent);

					LogHelper(const LogHelper&) = delete;

					LogHelper(LogHelper&& lh);

					~LogHelper();

					LogHelper& operator=(const LogHelper&) = delete;

					LogHelper& operator=(LogHelper&& lh);

					void Release();

					template <typename T>
					LogHelper& operator<< (const T& message)
					{
						m_buffer << message;

						return (*this);
					}

					LogHelper& operator<< (std::ostream& (*fn)(std::ostream& os));
				};
			};
		}
	}
}

#endif