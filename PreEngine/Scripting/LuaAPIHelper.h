#ifndef LUA_API_HELPER_H
#define LUA_API_HELPER_H

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "../Core/Common.h"
#include "ScriptingException.h"

namespace PreEngine
{
	namespace Scripting
	{
		using namespace PreEngine::Utils;

		class LuaAPIHelper
		{
		public:
			static void RunLuaScript(lua_State* L, const std::string& scriptName);

			static std::string PopLuaString(lua_State* pL, const std::string& name);

			static bool PopLuaBool(lua_State* pL, const std::string& name);

			static std::string PopLuaStringFieldFromTable(lua_State* L, const std::string& key);

			template <class T>
			static T PopLuaNumber(lua_State* pL, const std::string& name);

			template <class T>
			static T LuaPopNumberFieldFromTable(lua_State* L, const std::string& key);

			template <class T>
			static T PopLuaTopNumber(lua_State* pL);

			static void DumpStack(lua_State* L);

			static void RunLuaChunk(lua_State* L, std::string code);
		};

		template <class T>
		T LuaAPIHelper::PopLuaNumber(lua_State* pL, const std::string& name)
		{
			lua_settop(pL, 0);

			lua_getglobal(pL, name.c_str());
			if (!lua_isnumber(pL, 1))
			{
				throw new ScriptingException("<PopLuaNumber> Cannot retrieve: " + name);
			}

			T val = (T)lua_tonumber(pL, 1);
			lua_pop(pL, 1);

			return val;
		}

		template <class T>
		T LuaAPIHelper::PopLuaTopNumber(lua_State* pL)
		{
			int top = lua_gettop(pL);

			if (!lua_isnumber(pL, top))
			{
				throw new ScriptingException("<PopLuaTopNumber> Cannot get top of stack");
			}

			T val = (T)lua_tonumber(pL, top);
			lua_pop(pL, top);
			return val;
		}

		template <class T>
		T LuaAPIHelper::LuaPopNumberFieldFromTable(lua_State* L, const std::string& key)
		{
			lua_pushstring(L, key.c_str());

			lua_gettable(L, -2);
			if (!lua_isnumber(L, -1))
			{
				throw new ScriptingException("<LuaPopNumberFieldFromTable> Cannot retrieve: " + key);
			}

			T val = (T)lua_tonumber(L, -1);
			lua_pop(L, 1);

			return val;
		}
	}
}

#endif