#include "LuaAPIHelper.h"


namespace PreEngine
{
	namespace Scripting
	{
		void LuaAPIHelper::RunLuaScript(lua_State* L, const std::string& scriptName)
		{
			int error = luaL_dofile(L, scriptName.c_str());
			if (error != 0)
			{
				throw new ScriptingException("ERROR(" + StringUtils::ToString(error) + "): Problem with lua script file " + scriptName);
			}
		}

		std::string LuaAPIHelper::PopLuaString(lua_State* pL, const std::string& name)
		{
			lua_settop(pL, 0);

			lua_getglobal(pL, name.c_str());
			if (!lua_isstring(pL, 1))
			{
				throw new ScriptingException("<PopLuaString> Cannot retrieve: " + name);
			}

			std::string retString = lua_tostring(pL, 1);
			lua_pop(pL, 1);

			return retString;
		}

		bool LuaAPIHelper::PopLuaBool(lua_State* pL, const std::string& name)
		{
			lua_settop(pL, 0);

			lua_getglobal(pL, name.c_str());
			if (!lua_isstring(pL, 1))
			{
				throw new ScriptingException("<PopLuaBool> Cannot retrieve: " + name);
			}

			bool b = lua_toboolean(pL, 1) != 0;
			lua_pop(pL, 1);

			return b;
		}

		std::string LuaAPIHelper::PopLuaStringFieldFromTable(lua_State* L, const std::string& key)
		{
			lua_pushstring(L, key.c_str());

			lua_gettable(L, -2);

			if (!lua_isstring(L, -1))
			{
				throw new ScriptingException("<LuaPopStringFieldFromTable> Cannot retrieve: " + key);
			}

			std::string s = lua_tostring(L, -1);
			lua_pop(L, 1);

			return s;
		}

		void LuaAPIHelper::RunLuaChunk(lua_State* L, std::string code)
		{
			if (luaL_dostring(L, code.c_str()) != 0)
			{
				throw new ScriptingException("<RunLuaChunk> Cannot run provided chunk of code: " + code);
			}
		}

		void LuaAPIHelper::DumpStack(lua_State* L)
		{
			int top = lua_gettop(L);
			for (int i = 1; i <= top; i++)
			{
				int t = lua_type(L, i);
				switch (t)
				{
				case LUA_TSTRING:
					std::cout << "String: " << lua_tostring(L, i);
					break;

				case LUA_TBOOLEAN:
					std::cout << "Bool: " << lua_toboolean(L, i) ? "true" : "false";
					break;

				case LUA_TNUMBER:
					std::cout << "Number: " << lua_tonumber(L, i);
					break;

				default:
					std::cout << "Other: " << lua_typename(L, t);
					break;

				}
				std::cout << "  ";
			}
			std::cout << std::endl;
		}
	}
}