#pragma once

#include <string>
#include <cstdio>
#include <typeinfo>

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
		printf("%s: %s\n", typeid(*this).name(), stMessage.c_str());
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

struct LimitationException final : Exception
{
	inline LimitationException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCastException final : Exception
{
	inline BadCastException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCallException final : Exception
{
	inline BadCallException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct ArgumentException final : Exception
{
	inline ArgumentException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct InstanceException final : Exception
{
	inline InstanceException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct SymbolException final : Exception
{
	inline SymbolException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct AccessViolationException final : Exception
{
	inline AccessViolationException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct AllocationException final : Exception
{
	inline AllocationException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

}
}