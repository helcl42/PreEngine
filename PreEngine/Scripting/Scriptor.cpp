#include "Scriptor.h"

namespace PreEngine
{
	namespace Scripting
	{
		Scriptor::Scriptor()
			: m_luaState(luaL_newstate())
		{
		}

		Scriptor::~Scriptor()
		{
			lua_close(m_luaState);
		}

		void Scriptor::RunScriptFile(const std::string& ScriptName)
		{
			LuaAPIHelper::RunLuaScript(m_luaState, ScriptName);
		}

		lua_State* Scriptor::GetState() const
		{
			return m_luaState;
		}

		int Scriptor::GetInt(const std::string& VariableName)
		{
			return LuaAPIHelper::PopLuaNumber<int>(m_luaState, VariableName);
		}

		double Scriptor::GetFloat(const std::string& VariableName)
		{
			return LuaAPIHelper::PopLuaNumber<float>(m_luaState, VariableName);
		}

		double Scriptor::GetDouble(const std::string& VariableName)
		{
			return LuaAPIHelper::PopLuaNumber<double>(m_luaState, VariableName);
		}

		std::string Scriptor::GetString(const std::string& VariableName)
		{
			return LuaAPIHelper::PopLuaString(m_luaState, VariableName);
		}

		bool Scriptor::GetBool(const std::string& VariableName)
		{
			return LuaAPIHelper::PopLuaBool(m_luaState, VariableName);
		}

		double Scriptor::PopTopDouble()
		{
			return LuaAPIHelper::PopLuaTopNumber<double>(m_luaState);
		}

		float Scriptor::PopTopFloat()
		{
			return LuaAPIHelper::PopLuaTopNumber<float>(m_luaState);
		}

		int Scriptor::PopTopInt()
		{
			return LuaAPIHelper::PopLuaTopNumber<int>(m_luaState);
		}

		double Scriptor::GetDoubleResult(const std::string& code)
		{
			LuaAPIHelper::RunLuaChunk(m_luaState, "return " + code);
			return PopTopDouble();
		}

		float Scriptor::GetFloatResult(const std::string& code)
		{
			LuaAPIHelper::RunLuaChunk(m_luaState, "return " + code);
			return PopTopFloat();
		}

		int Scriptor::GetIntResult(const std::string& code)
		{
			LuaAPIHelper::RunLuaChunk(m_luaState, "return " + code);
			return PopTopInt();
		}

		void Scriptor::RunChunk(const std::string& code)
		{
			LuaAPIHelper::RunLuaChunk(m_luaState, code);
		}

		void Scriptor::DumpStack()
		{
			LuaAPIHelper::DumpStack(m_luaState);
		}
	}
}