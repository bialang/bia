#pragma once

#include "class_template_def.hpp"
#include "machine_context.hpp"
#include "object.hpp"
#include "member_map.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
inline class_template<Type>::class_template()
{
	_data.get().second = machine::machine_context::active_allocator()->template construct<force::initiator>();
}

template<typename Type>
inline class_template<Type>::class_template(const data_type & _data) noexcept : _data(_data)
{
}

template<typename Type>
inline class_template<Type>::~class_template()
{
	if (_data.only_owner()) {
		machine::machine_context::active_allocator()->template destroy(_data.get().second);
	}
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::print() const
{
	printf("<class_template of %s>\n", typeid(Type).name());
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::copy(member * _destination)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::refer(member * _destination)
{
	return void BIA_MEMBER_CALLING_CONVENTION();
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::execute(member * _destination)
{
	instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate()), true);

	_destination->template replace_this<object<Type>>(_instance, _data.get().first);
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION class_template<Type>::execute_count(member * _destination, void * _reserved, parameter_count _count...)
{
	force::va_list_wrapper _args;
	va_start(_args.args, _count);
	auto _instance_created = false;

	try {
		instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate_count(_count, _args)), true);
		_destination->replace_this<object<Type>>(_instance, _data.get().first);

		_instance_created = true;
		va_end(_args.args);

		_destination->replace_this<object<Type>>(_instance, _data.get().first);
	} catch (...) {
		if (!_instance_created) {
			va_end(_args.args);
		}

		throw;
	}
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION class_template<Type>::execute_format(member * _destination, const char * _format, parameter_count _count...)
{
	force::va_list_wrapper _args;
	va_start(_args.args, _count);
	auto _instance_created = false;

	try {
		instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate_format(_format, _count, _args)), true);

		_instance_created = true;
		va_end(_args.args);

		_destination->replace_this<object<Type>>(_instance, _data.get().first);
	} catch (...) {
		if (!_instance_created) {
			va_end(_args.args);
		}

		throw;
	}
}

template<typename Type>
template<typename ...Arguments>
inline void class_template<Type>::set_constructor()
{
	auto _allocator = machine::machine_context::active_allocator();

	_allocator->destroy(_data.get().second);
	_data.get().second = _allocator->construct<force::initiator, force::real_initiator<Type, Arguments...>>();
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::object_member(member * _destination, member_map::name_type _name)
{
	_data.get().first.get(_name)->refer(_destination);
}

template<typename Type>
inline int class_template<Type>::flags() const
{
	return F_NONE;
}

template<typename Type>
inline member_map & class_template<Type>::members() noexcept
{
	return _data.get().first;
}

}
}
}
