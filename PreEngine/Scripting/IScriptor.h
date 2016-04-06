#ifndef ISCRIPTOR_H
#define ISCRIPTOR_H

#include "../Core/Common.h"
#include "ScriptingException.h"
#include "LuaAPIHelper.h"

namespace PreEngine
{
	namespace Scripting
	{
		class IScriptor
		{
		public:
			virtual void RunScriptFile(const std::string& ScriptName) = 0;

			virtual lua_State* GetState() const = 0;

			virtual int GetInt(const std::string& VariableName) = 0;

			virtual double GetFloat(const std::string& VariableName) = 0;

			virtual double GetDouble(const std::string& VariableName) = 0;

			virtual std::string GetString(const std::string& VariableName) = 0;

			virtual bool GetBool(const std::string& VariableName) = 0;

			virtual void RunChunk(const std::string& code) = 0;

			virtual double PopTopDouble() = 0;

			virtual float PopTopFloat() = 0;

			virtual int PopTopInt() = 0;

			virtual double GetDoubleResult(const std::string& code) = 0;

			virtual float GetFloatResult(const std::string& code) = 0;

			virtual int GetIntResult(const std::string& code) = 0;

			virtual void DumpStack() = 0;

		public:
			virtual ~IScriptor() {}
		};
	}
}

#endif