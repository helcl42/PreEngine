#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		class StringUtils
		{
		public:
			static std::string GetTypeName(std::string typeName);

			static std::string GetCanonicalTypeName(std::string typeName);

			static std::string& StringUtils::Trim(std::string& str);

			static std::vector<std::string>& Split(const std::string &s, char delim, std::vector<std::string> &elems);

			static std::vector<std::string> StringUtils::Split(std::string s, std::string t);

			static std::string Replace(std::string& subject, const std::string& search, const std::string& replace);

			template <class T>
			inline static std::string ToString(const T& t, int precision = 2)
			{
				std::ostringstream buffer;
				buffer << std::fixed << std::setprecision(precision) << t;
				return buffer.str();
			}
			
			inline static std::string ToString(bool b);
			
			template <class T>
			inline static T GetValueFromStream(std::ifstream& stream);

			inline static void RemoveQuotes(std::string& str);
		};
	}
}

#endif