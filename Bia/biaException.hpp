#pragma once

#include <string>
#include <stdio.h>

#define BIA_IMPLEMENTATION_EXCEPTION(msg) bia::exception::ImplementationException(msg, __FILE__, __LINE__)


namespace bia
{
namespace exception
{

struct Exception
{
	std::string stMessage;

	inline Exception(std::string p_stMessage) : stMessage(std::move(p_stMessage)) {}
	virtual ~Exception() = default;
	inline virtual void Print() const
	{
		printf("%s\n", stMessage.c_str());
	}
};

/**
 * @brief	Thrown when an implementation related error occurred. These kind of error should be reported to the maintainer of the code.
*/
struct ImplementationException final : Exception
{
	inline ImplementationException(std::string p_stMessage, const char * p_pszFile, int p_nLine) : Exception(p_pszFile + std::string(":") + std::to_string(p_nLine) + ": " + std::move(p_stMessage)) {}
};

/**
 * @brief	Thrown when a operator specific invalid operation was executed (e.g. bitwise operation with floating point values).
*/
struct OperatorException final : Exception
{
	inline OperatorException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct NumberException final : Exception
{
	inline NumberException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCastException final : Exception
{
	inline BadCastException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCallException final : Exception
{
	inline BadCallException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct SymbolException final : Exception
{
	inline SymbolException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct AccessViolationException final : Exception
{
	inline AccessViolationException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

}
}