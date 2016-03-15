#include "StringUtils.h"


namespace PreEngine
{
	namespace Utils
	{
		std::string StringUtils::GetTypeName(std::string typeName)
		{
			std::string retName = StringUtils::Replace(typeName, "class ", "");
			return StringUtils::Replace(retName, "struct ", "");
		}

		std::string StringUtils::GetCanonicalTypeName(std::string typeName)
		{
			std::string retName = GetTypeName(typeName);
			if (retName.find_last_of(':') != retName.npos)
			{
				retName = retName.substr(retName.find_last_of(':') + 1);
			}
			retName = StringUtils::Replace(retName, "<", "_");
			retName = StringUtils::Replace(retName, ">", "_");
			return retName;
		}

		std::string& StringUtils::Trim(std::string& str) 
		{
			const char * whiteSpace = " \t\n\r";
			str.erase(0, str.find_first_not_of(whiteSpace));
			str.erase(str.find_last_not_of(whiteSpace) + 1);
			return str;
		}

		std::vector<std::string>& StringUtils::Split(const std::string &s, char delim, std::vector<std::string> &elems)
		{
			std::istringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim))
			{
				elems.push_back(item);
			}
			return elems;
		}

		std::vector<std::string> StringUtils::Split(std::string s, std::string t)
		{
			std::vector<std::string> res;
			while (true)
			{
				size_t pos = s.find(t);
				if (pos == -1)
				{
					res.push_back(s); 
					break;
				}
				res.push_back(s.substr(0, pos));
				s = s.substr(pos + 1, s.size() - pos - 1);
			}
			return res;
		}

		std::string StringUtils::Replace(std::string& subject, const std::string& search, const std::string& replace)
		{
			size_t pos = 0;
			while ((pos = subject.find(search, pos)) != std::string::npos)
			{
				subject.replace(pos, search.length(), replace);
				pos += replace.length();
			}
			return std::string(subject);
		}

		std::string StringUtils::ToString(bool b)
		{
			if (b) return "true";
			return "false";
		}

		template <class T>
		T StringUtils::GetValueFromStream(std::ifstream& stream)
		{
			T val;
			stream >> val;
			if (!stream)
			{
				throw std::runtime_error("Attempting to retrieve wrong type from stream");
			}
			return val;
		}

		void StringUtils::RemoveQuotes(std::string& str)
		{
			size_t n;
			while ((n = str.find('\"')) != std::string::npos)
			{
				str.erase(n, 1);
			}
		}
	}
}
