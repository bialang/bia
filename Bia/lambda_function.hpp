#pragma once

#include <cstdarg>
#include <utility>

#include "lambda_function_def.hpp"
#include "disguised_caller.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<typename Lambda>
inline lambda_function<Lambda>::lambda_function(const Lambda & _lambda) : _data(_lambda)
{
}

template<typename Lambda>
inline lambda_function<Lambda>::lambda_function(Lambda && _lambda) : _data(std::move(_lambda))
{
}

template<typename Lambda>
inline lambda_function<Lambda>::lambda_function(const data_type & _data) noexcept : _data(_data)
{
}

template<typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::print() const
{
	puts(typeid(&Lambda::operator()).name());
}

template<typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::copy(member * _destination)
{
	_destination->replace_this<lambda_function<Lambda>>(_data.get());
}

template<typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::refer(member * _destination)
{
	_destination->replace_this<lambda_function<Lambda>>(_data);
}

template<typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::clone(member * _destination)
{
	refer(_destination);
}

template<typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::execute(member * _destination)
{
	force::disguised_caller(&Lambda::operator(), &_data.get(), _destination);
}

template<typename Lambda>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::execute_count(member * _destination, void * _reserved, parameter_count _count...)
{
	force::va_list_wrapper _args;
	va_start(_args.args, _count);

	force::disguised_caller_count(&Lambda::operator(), &_data.get(), _destination, _count, _args);

	va_end(_args.args);
}

template<typename Lambda>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION lambda_function<Lambda>::execute_format(member * _destination, const char * _format, parameter_count _count...)
{
	force::va_list_wrapper _args;
	va_start(_args.args, _count);

	force::disguised_caller_format(&Lambda::operator(), &_data.get(), _destination, _format, _count, _args);

	va_end(_args.args);
}

template<typename Lambda>
inline void lambda_function<Lambda>::set_instance(const void * _instance, const std::type_info & _type)
{
}

}
}
}