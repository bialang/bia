#pragma once

#include <string>
#include <cstdio>
#include <typeinfo>
#include <exception>

#define BIA_IMPLEMENTATION_EXCEPTION(msg) bia::exception::implementation_error(msg, __FILE__, __LINE__)
#define BIA_EM_UNSUPPORTED_TYPE "Type is not supported."
#define BIA_EM_UNDEFINED_MEMBER "Undefined member."


namespace bia
{
namespace exception
{

class bia_error
{
public:
	virtual ~bia_error() = default;
};

class logic_error : public bia_error, public std::logic_error
{
public:
	explicit logic_error(const std::string & _message) : std::logic_error(_message)
	{
	}
	explicit logic_error(const char * _message) : std::logic_error(_message)
	{
	}
};

class runtime_error : public bia_error, public std::runtime_error
{
public:
	explicit runtime_error(const std::string & _message) : std::runtime_error(_message)
	{
	}
	explicit runtime_error(const char * _message) : std::runtime_error(_message)
	{
	}
};

class invalid_type : public logic_error
{
public:
	explicit invalid_type(const std::string & _message) : logic_error(_message)
	{
	}
	explicit invalid_type(const char * _message) : logic_error(_message)
	{
	}
};

class symbol_error final : public runtime_error
{
public:
	explicit symbol_error(const std::string & _message) : runtime_error(_message)
	{
	}
	explicit symbol_error(const char * _message) : runtime_error(_message)
	{
	}
};

}
}