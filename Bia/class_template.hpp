#pragma once

#include "class_template_def.hpp"
#include "machine_context.hpp"
#include "object.hpp"
#include "member_map.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
inline class_template<Type>::data_pair::~data_pair()
{
	machine::machine_context::active_allocator()->destroy(second);
}

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
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::print() const
{
	printf("<class_template of %s>\n", typeid(Type).name());
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::copy(member * _destination)
{
	throw exception::execution_error(BIA_EM_UNSUPPORTED_COPY);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::refer(member * _destination)
{
	_destination->replace_this<class_template>(_data);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::execute(member * _destination)
{
	instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate()), true);

	_destination->template replace_this<object<Type>>(_instance, _data.get().first);
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION class_template<Type>::execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack)
{
	instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate_count(_count, _stack)), true);

	_destination->replace_this<object<Type>>(_instance, _data.get().first);
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION class_template<Type>::execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack)
{
	instance_holder<Type> _instance(machine::memory::cast_allocation<Type>(_data.get().second->instantiate_format(_format, _count, _stack)), true);

	_destination->replace_this<object<Type>>(_instance, _data.get().first);
}

template<typename Type>
template<size_t Optional_count, typename ...Arguments>
inline void class_template<Type>::set_constructor()
{
	auto _allocator = machine::machine_context::active_allocator();

	_allocator->destroy(_data.get().second);
	_data.get().second = _allocator->construct<force::initiator, force::real_initiator<Optional_count, Type, Arguments...>>();
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION class_template<Type>::object_member(member * _destination, member_map::name_t _name)
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
