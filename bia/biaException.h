#pragma once

#include <string>
#include <stdio.h>


namespace bia
{
namespace exception
{

struct Exception
{
	std::string stMessage;
	
	inline Exception(std::string p_stMessage) : stMessage(std::move(p_stMessage)) {}
	inline virtual ~Exception() = default;
	inline virtual void Print() const
	{
		printf("%s\n", stMessage.c_str());
	}
};

struct UnknownException final : Exception
{
	inline UnknownException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct UnknownTemplateException final : Exception
{
	inline UnknownTemplateException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct DivisionByZeroException final : Exception
{
	inline DivisionByZeroException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct ArgumentException final : Exception
{
	inline ArgumentException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct TypeException final : Exception
{
	inline TypeException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct ReservedTypeException final : Exception
{
	inline ReservedTypeException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct InvalidByteCodeException final : Exception
{
	inline InvalidByteCodeException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadByteCodeException final : Exception
{
	inline BadByteCodeException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCastException final : Exception
{
	inline BadCastException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct BadCallException final : Exception
{
	inline BadCallException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
};

struct RestrictionException final : Exception
{
	inline RestrictionException(std::string p_stMessage) : Exception(std::move(p_stMessage)) {}
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