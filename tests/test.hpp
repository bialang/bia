#pragma once

#include <biaMachineContext.hpp>
#include <biaMember.hpp>
#include <cstring>
#include <exception>

#define BIA_ASSERT(expr, msg) if(!(expr))throw msg;


template<typename T>
inline bool TestValue(bia::machine::BiaMachineContext & p_context, const std::string & p_stVariable, T p_value)
{
	//Get variable
	auto pVariable = p_context.GetGlobal(p_stVariable);

	BIA_ASSERT(pVariable != nullptr, "Variable not found.");

	//Get value
	auto pValue = pVariable->Cast<T>();

	BIA_ASSERT(pValue != nullptr, "Invalid type.");
	BIA_ASSERT(*pValue == p_value, "Values don't match.");

	return true;
}

template<typename T>
inline bool TestValue(bia::framework::BiaMember & p_member, T p_value)
{
	//Get value
	auto pValue = p_member.Cast<T>();

	BIA_ASSERT(pValue != nullptr, "Invalid type.");
	BIA_ASSERT(*pValue == p_value, "Values don't match.");

	return true;
}

inline bool TestValue(bia::framework::BiaMember & p_member, const char * p_szValue)
{
	//Get value
	auto pValue = p_member.Cast<const char*>();

	BIA_ASSERT(pValue != nullptr, "Invalid type.");
	BIA_ASSERT(std::strcmp(*pValue, p_szValue) == 0, "Values don't match.");

	return true;
}