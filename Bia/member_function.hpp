#pragma once

#include "member_function_def.hpp"
#include "exception.hpp"
#include "disguised_caller_def.hpp"
#include "share.hpp"
#include "instance_holder.hpp"


namespace bia
{
namespace framework
{
namespace executable
{

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline member_function<Optional_count, Return(Class::*)(Arguments...)>::member_function(Return(Class::* _function)(Arguments...)) noexcept : _data(_function, object::instance_holder<Class>(machine::memory::allocation<Class>(), false))
{
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline member_function<Optional_count, Return(Class::*)(Arguments...)>::member_function(const data_type & _data) noexcept : _data(_data)
{
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::print() const
{
	puts(typeid(Return(Class::*)(Arguments...)).name());
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::copy(member * _destination)
{
	_destination->replace_this<member_function<Optional_count, Return(Class::*)(Arguments...)>>(_data.get().first);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::refer(member * _destination)
{
	_destination->replace_this<member_function<Optional_count, Return(Class::*)(Arguments...)>>(_data);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::clone(member * _destination)
{
	refer(_destination);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::execute(member * _destination)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, nullptr, 0, nullptr);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, nullptr, _count, _stack);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION member_function<Optional_count, Return(Class::*)(Arguments...)>::execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, _format, _count, _stack);
}

template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline void member_function<Optional_count, Return(Class::*)(Arguments...)>::set_instance(const void * _instance, const std::type_info & _type)
{
	if (_type != typeid(Class)) {
		throw exception::type_error(BIA_EM_INVALID_INSTANCE_TYPE);
	}

	/// TODO
	_data.get().second.~instance_holder();
	new(&_data.get().second) object::instance_holder<Class>(*static_cast<const object::instance_holder<Class>*>(_instance));
}


template<size_t Optional_count, typename Class, typename Return, typename ...Arguments>
inline Class * member_function<Optional_count, Return(Class::*)(Arguments...)>::cast_instance()
{
	auto _instance = _data.get().second.get();

	if (_instance) {
		return _instance;
	} else {
		throw exception::argument_error(BIA_EM_NULL_INSTANCE);
	}
}

}
}
}