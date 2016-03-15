#ifndef SCRIPTOR_H
#define SCRIPTOR_H

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "../Core/Common.h"
#include "ScriptingException.h"
#include "LuaAPIHelper.h"
#include "IScriptor.h"

namespace PreEngine
{
	namespace Scripting
	{		
		class Scriptor : public IScriptor
		{
		private:
			lua_State* m_luaState;

		public:
			Scriptor();

			virtual ~Scriptor();

		public:
			void RunScriptFile(const std::string& ScriptName);

			lua_State* GetState() const;

			int GetInt(const std::string& VariableName);

			double GetFloat(const std::string& VariableName);

			double GetDouble(const std::string& VariableName);

			std::string GetString(const std::string& VariableName);

			bool GetBool(const std::string& VariableName);

			void RunChunk(const std::string& code);

			double PopTopDouble();

			float PopTopFloat();

			int PopTopInt();

			double GetDoubleResult(const std::string& code);

			float GetFloatResult(const std::string& code);

			int GetIntResult(const std::string& code);

			void DumpStack();
		};
	}
}

#endif