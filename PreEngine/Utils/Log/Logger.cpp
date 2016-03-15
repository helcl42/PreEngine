#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "Logger.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Log
		{
			Logger Logger::s_instance;

			Logger::Logger()
			{
			}

			Logger& Logger::GetInstance()
			{
				return s_instance;
			}

			void Logger::SetOutputFileName(const std::string& fileName)
			{
				m_outputFile.open(fileName, std::ofstream::out);
				if (!m_outputFile.is_open()) throw new LoggerException("Could not open: " + fileName);
				m_outputFile.sync_with_stdio(false); // turn off stdio sync!
			}

			Logger::LogHelper Logger::operator << (std::ostream& (*fn)(std::ostream& os))
			{
				LogHelper helper(this);

				fn(helper.m_buffer);

				return helper;
			}

			std::string clockString(const std::chrono::system_clock::time_point& tp) 
			{
				auto timeStruct = std::chrono::system_clock::to_time_t(tp);

				// converting a time_t to a string is one of those locale-influenced thingies
				// and is affected by imbued iostreams. However, I'm not really inclined to
				// use anything other than the system default. 
				// for more information (and formatting options) search std::put_time @ cppreference
				// [Note] This is the C-standard library, so the microsoft implementation is *not* up to date (grmbl)
				//	in the documentation, assume that if it says C++11 it won't work...

				std::stringstream sstr;

#pragma warning(push)
#pragma warning(disable: 4996) // the call to 'localtime' is 'unsafe'...
				sstr << std::put_time(std::localtime(&timeStruct), "%H:%M:%S"); // hour/minutes/seconds
#pragma warning(pop)

				return sstr.str();
			}

			Logger::LogHelper::LogHelper(Logger* parent) :
				m_parent(parent)
			{
				m_buffer << clockString(std::chrono::system_clock::now());
			}

			Logger::LogHelper::LogHelper(LogHelper&& lh)
				: m_parent(std::move(lh.m_parent)), m_buffer(std::move(lh.m_buffer))
			{
				lh.Release();
			}

			Logger::LogHelper::~LogHelper()
			{
				try
				{
					if (m_parent)
					{
						m_buffer << std::endl;
						m_parent->Flush(m_buffer.str());
					}
				}
				catch (...)
				{
					std::cerr << "Failed to flush to log!" << std::endl;
				}
			}

			Logger::LogHelper& Logger::LogHelper::operator= (LogHelper&& lh)
			{
				m_parent = std::move(lh.m_parent);
				m_buffer = std::move(lh.m_buffer);

				lh.Release();

				return (*this);
			}

			void Logger::LogHelper::Release()
			{
				m_parent = nullptr;
			}

			Logger::LogHelper& Logger::LogHelper::operator << (std::ostream& (*fn)(std::ostream& os))
			{
				fn(m_buffer);
				return (*this);
			}

			void Logger::Flush(std::string message)
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_outputFile << message;				
#ifdef _DEBUG
				std::clog << message;
#endif
			}

			Logger::LogHelper Logger::Debug()
			{
				LogHelper helper(this);

				helper << " [dbg] ";

				return helper;
			}

			Logger::LogHelper Logger::Info()
			{
				LogHelper helper(this);

				helper << "       ";

				return helper;
			}

			Logger::LogHelper Logger::Warning()
			{
				LogHelper helper(this);

				helper << " [WARN] ";

				return helper;
			}

			Logger::LogHelper Logger::Error()
			{
				LogHelper helper(this);

				helper << " [** ERROR **] ";

				return helper;
			}

			Logger::LogHelper Logger::Fatal()
			{
				LogHelper helper(this);

				helper << " [<=== FATAL ===>] ";

				return helper;
			}
		}
	}
}