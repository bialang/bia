#pragma once

#include <type_traits>
#include <cstdarg>

#include "object_def.hpp"
#include "share.hpp"
#include "constructor_chain.hpp"
#include "machine_context.hpp"
#include "member_map.hpp"
#include "instance_holder.hpp"


namespace bia
{
namespace framework
{
namespace object
{

template<typename Type>
inline object<Type>::object(const instance_holder<Type> & _instance, const member_map & _members) noexcept : _data(_instance, _members)
{
}

template<typename Type>
inline object<Type>::object(const data_type & _data) noexcept : _data(_data)
{
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::print() const
{
	printf("<%s at %p>\n", typeid(Type).name(), this);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::copy(member * _destination)
{
	instance_holder<Type> _instance(constructor_chain_wrapper<Type>(machine::machine_context::active_allocator(), *_data.get().first.get()), true);

	_destination->replace_this<object<Type>>(_instance, _data.get().second);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::refer(member * _destination)
{
	_destination->replace_this<object<Type>>(_data);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::execute(member * _destination)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION object<Type>::execute_count(member * _destination, void * _reserved, parameter_count _count...)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_VARG_MEMBER_CALLING_CONVENTION object<Type>::execute_format(member * _destination, const char * _format, parameter_count _count...)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION object<Type>::object_member(member * _destination, machine::string_manager::name_t _name)
{
	// Get instance, because this could be _destination
	auto _instance = _data.get().first;

	_data.get().second.get(_name)->copy(_destination);

	_destination->set_instance(&_instance, typeid(Type));
}

template<typename Type>
inline int object<Type>::flags() const
{
	return F_NONE;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION object<Type>::test() const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION object<Type>::test_member(operator_type _operator, member * _right) const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION object<Type>::test_int32(operator_type _operator, int32_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION object<Type>::test_int64(operator_type _operator, int64_t _right) const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION object<Type>::test_double(operator_type _operator, double _right) const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int64_t object<Type>::to_int() const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline double object<Type>::to_double() const
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int32_t object<Type>::int32_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
inline int64_t object<Type>::int64_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
inline double object<Type>::double_data() const
{
	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
inline void * object<Type>::data(const std::type_info & _type)
{
	if (!std::is_const<Type>::value) {
		if (typeid(Type) == _type) {
			return _data.get().first.get().first;
		}
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
inline const void * object<Type>::const_data(const std::type_info & _type) const
{
	if (typeid(Type) == _type) {
		return _data.get().first.get().first;
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

}
}
}
