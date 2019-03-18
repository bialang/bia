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

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline member_function<Optional_count, _Return(_Class::*)(_Args...)>::member_function(_Return(_Class::* _function)(_Args...)) noexcept : _data(_function, object::instance_holder<_Class>(machine::memory::allocation<_Class>(), false))
{
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline member_function<Optional_count, _Return(_Class::*)(_Args...)>::member_function(const data_type & _data) noexcept : _data(_data)
{
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::print() const
{
	puts(typeid(_Return(_Class::*)(_Args...)).name());
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::copy(member * _destination)
{
	_destination->replace_this<member_function<Optional_count, _Return(_Class::*)(_Args...)>>(_data.get().first);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::refer(member * _destination)
{
	_destination->replace_this<member_function<Optional_count, _Return(_Class::*)(_Args...)>>(_data);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::clone(member * _destination)
{
	refer(_destination);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::execute(member * _destination)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, nullptr, 0, nullptr);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, nullptr, _count, _stack);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION member_function<Optional_count, _Return(_Class::*)(_Args...)>::execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack)
{
	force::disguised_caller<Optional_count>(cast_instance(), _data.get().first, _destination, _format, _count, _stack);
}

template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline void member_function<Optional_count, _Return(_Class::*)(_Args...)>::set_instance(const void * _instance, const std::type_info & _type)
{
	if (_type != typeid(_Class)) {
		throw exception::type_error(BIA_EM_INVALID_INSTANCE_TYPE);
	}

	/// TODO
	_data.get().second.~instance_holder();
	new(&_data.get().second) object::instance_holder<_Class>(*static_cast<const object::instance_holder<_Class>*>(_instance));
}


template<size_t Optional_count, typename _Class, typename _Return, typename ..._Args>
inline _Class * member_function<Optional_count, _Return(_Class::*)(_Args...)>::cast_instance()
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