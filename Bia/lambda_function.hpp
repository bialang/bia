#pragma once

#include <cstdarg>
#include <utility>

#include "lambda_function_def.hpp"
#include "disguised_caller_def.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<size_t Optional_count, typename Lambda>
inline lambda_function<Optional_count, Lambda>::lambda_function(const Lambda & _lambda) : _data(_lambda)
{
}

template<size_t Optional_count, typename Lambda>
inline lambda_function<Optional_count, Lambda>::lambda_function(Lambda && _lambda) : _data(std::move(_lambda))
{
}

template<size_t Optional_count, typename Lambda>
inline lambda_function<Optional_count, Lambda>::lambda_function(const data_type & _data) noexcept : _data(_data)
{
}

template<size_t Optional_count, typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::print() const
{
	puts(typeid(&Lambda::operator()).name());
}

template<size_t Optional_count, typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::copy(member * _destination)
{
	_destination->replace_this<lambda_function<Optional_count, Lambda>>(_data.get());
}

template<size_t Optional_count, typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::refer(member * _destination)
{
	_destination->replace_this<lambda_function<Optional_count, Lambda>>(_data);
}

template<size_t Optional_count, typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::clone(member * _destination)
{
	refer(_destination);
}

template<size_t Optional_count, typename Lambda>
inline void BIA_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::execute(machine::stack * _stack, member * _destination)
{
	force::disguised_caller<Optional_count>(&_data.get(), &Lambda::operator(), _destination, nullptr, 0, nullptr);
}

template<size_t Optional_count, typename Lambda>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::execute_count(machine::stack * _stack, member * _destination, void * _reserved, parameter_count_t _count)
{
	force::disguised_caller<Optional_count>(&_data.get(), &Lambda::operator(), _destination, nullptr, _count, _stack);
}

template<size_t Optional_count, typename Lambda>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION lambda_function<Optional_count, Lambda>::execute_format(machine::stack * _stack, member * _destination, const char * _format, parameter_count_t _count)
{
	force::disguised_caller<Optional_count>(&_data.get(), &Lambda::operator(), _destination, _format, _count, _stack);
}

template<size_t Optional_count, typename Lambda>
inline void lambda_function<Optional_count, Lambda>::set_instance(const void * _instance, const std::type_info & _type)
{
}

}
}
}