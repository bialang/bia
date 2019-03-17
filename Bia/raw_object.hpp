#pragma once

#include <cstdarg>
#include <utility>

#include "raw_object_def.hpp"
#include "constructor_chain.hpp"
#include "instance_holder.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
template<typename Ty, typename Switch>
inline raw_object<Type>::raw_object(Ty && _object) : _data(constructor_chain_wrapper<Type>(machine::machine_context::active_allocator(), std::forward<Ty>(_object)), true)
{
}

template<typename Type>
inline raw_object<Type>::raw_object(const data_type & _data) noexcept : _data(_data)
{
}

template<typename Type>
inline raw_object<Type>::raw_object(machine::memory::allocation<Type> _object, bool _owner) noexcept : _data(_object, _owner)
{
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::print() const
{
	printf("<%s at %p>\n", typeid(Type).name(), this);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::copy(member * _destination)
{
	_destination->replace_this<raw_object<Type>>(constructor_chain_wrapper<Type>(machine::machine_context::active_allocator(), *_data.get()), true);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::refer(member * _destination)
{
	_destination->replace_this<raw_object<Type>>(_data);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::execute(member * _destination)
{
	promote()->execute(_destination);
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION raw_object<Type>::execute_count(member * _destination, void * _reserved, parameter_count_t _count, machine::stack * _stack)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION raw_object<Type>::execute_format(member * _destination, const char * _format, parameter_count_t _count, machine::stack * _stack)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::operator_call(member * _destination, operator_t _operator, const member * _right)
{
	return promote()->operator_call(_destination, _operator, _right);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::operator_call_int32(member * _destination, operator_t _operator, int32_t _right)
{
	return promote()->operator_call_int32(_destination, _operator, _right);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::operator_call_int64(member * _destination, operator_t _operator, int64_t _right)
{
	return promote()->operator_call_int64(_destination, _operator, _right);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::operator_call_double(member * _destination, operator_t _operator, double _right)
{
	return promote()->operator_call_double(_destination, _operator, _right);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::object_member(member * _destination, machine::name_manager::name_t _name)
{
	promote()->object_member(_destination, _name);
}

template<typename Type>
inline int raw_object<Type>::flags() const
{
	return F_NONE;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::test() const
{
	return promote()->test();
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::test_member(operator_t _operator, member * _right) const
{
	return promote()->test_member(_operator, _right);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::test_int32(operator_t _operator, int32_t _right) const
{
	return promote()->test_int32(_operator, _right);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::test_int64(operator_t _operator, int64_t _right) const
{
	return promote()->test_int64(_operator, _right);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION raw_object<Type>::test_double(operator_t _operator, double _right) const
{
	return promote()->test_double(_operator, _right);
}

template<typename Type>
inline int64_t raw_object<Type>::to_int() const
{
	return promote()->to_int();
}

template<typename Type>
inline double raw_object<Type>::to_double() const
{
	return promote()->to_double();
}

template<typename Type>
inline member * raw_object<Type>::promote() const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void * raw_object<Type>::data(const std::type_info & _type, bool & _success)
{
	if (!std::is_const<Type>::value) {
		if (typeid(Type) == _type) {
			_success = true;

			return _data.get().first;
		}
	}

	return nullptr;
}

template<typename Type>
inline const void * raw_object<Type>::const_data(const std::type_info & _type, bool & _success) const
{
	if (typeid(Type) == _type) {
		_success = true;

		return _data.get().first;
	}

	return nullptr;
}

}
}
}
