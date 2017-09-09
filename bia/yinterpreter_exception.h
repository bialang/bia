#pragma once

#include <string>

#include "yinterpreter_code.h"


namespace yu
{
namespace interpret
{

struct SToken;

struct Exception
{
public:
	inline Exception(std::string p_stMsg) : stMsg(std::move(p_stMsg)) {}
	inline virtual ~Exception() = default;

	const std::string stMsg;
};

struct UndefinedRule : Exception
{
	inline UndefinedRule(std::string p_stMsg, unsigned int p_uiRule) : Exception(std::move(p_stMsg)), uiRule(p_uiRule) {}

	const unsigned int uiRule;
};

struct UnsupportedToken : Exception
{
	inline UnsupportedToken(std::string p_stMsg, const SToken * p_pToken) : Exception(std::move(p_stMsg)), pToken(p_pToken) {}

	const SToken * pToken;
};

struct WrongEncoding : Exception
{
	inline WrongEncoding(std::string p_stMsg) : Exception(std::move(p_stMsg)) {}
};

struct OutOfBounds : Exception
{
	OutOfBounds(std::string p_stMsg) : Exception(std::move(p_stMsg)) {}
};

}
}