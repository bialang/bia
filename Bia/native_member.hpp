#pragma once

#include "native_member_def.hpp"
#include "native_variable.hpp"
#include "exception.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"
#include "print.hpp"
#include "share.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename Type>
inline native_member<Type>::native_member(typename std::enable_if<std::is_same<Type, int64_t>::value || std::is_same<Type, double>::value, Type>::type _value) : _data(_value, false)
{
}

template<typename Type>
inline native_member<Type>::native_member(const utility::share<std::pair<Type, bool>> & _data) noexcept : _data(_data)
{
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::print() const
{
	machine::link::print(_data.get().first);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::copy(member * _destination)
{
	create_result_member(_data.get().first, _destination);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::refer(member * _destination)
{
	_destination->replace_this<native_member<Type>>(_data);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::clone(member * _destination)
{
	copy(_destination);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::operator_call(member * _destination, operator_type _operator, const member * _right)
{
	if (std::is_same<Type, int64_t>::value) {
		create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right->to_int()), _destination);
	} else {
		create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right->to_double()), _destination);
	}
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::operator_call_int32(member * _destination, operator_type _operator, int32_t _right)
{
	create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
{
	create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::operator_call_double(member * _destination, operator_type _operator, double _right)
{
	create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
}

template<typename Type>
inline void BIA_MEMBER_CALLING_CONVENTION native_member<Type>::object_member(member * _destination, machine::string_manager::name_type _name)
{
	BIA_NOT_IMPLEMENTED;
}

template<typename Type>
inline int native_member<Type>::flags() const
{
	return F_TO_INT | F_TO_DOUBLE | (std::is_same<Type, int64_t>::value ? F_INT : F_DOUBLE);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION native_member<Type>::test() const
{
	return native::test(_data.get().first);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION native_member<Type>::test_member(operator_type _operator, member * _right) const
{
	if (std::is_same<Type, int64_t>::value) {
		return test_operation(_data.get().first, _operator, _right->to_int());
	} else {
		return test_operation(_data.get().first, _operator, _right->to_double());
	}
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION native_member<Type>::test_int32(operator_type _operator, int32_t _right) const
{
	return test_operation(_data.get().first, _operator, _right);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION native_member<Type>::test_int64(operator_type _operator, int64_t _right) const
{
	return test_operation(_data.get().first, _operator, _right);
}

template<typename Type>
inline int32_t BIA_MEMBER_CALLING_CONVENTION native_member<Type>::test_double(operator_type _operator, double _right) const
{
	return test_operation(_data.get().first, _operator, _right);
}

template<typename Type>
inline int64_t native_member<Type>::to_int() const
{
	return static_cast<int64_t>(_data.get().first);
}

template<typename Type>
inline double native_member<Type>::to_double() const
{
	return static_cast<double>(_data.get().first);
}

template<typename Type>
inline void * native_member<Type>::native_data(native::NATIVE_TYPE _type)
{
	// Integral
	if (std::is_same<Type, int64_t>::value) {
		switch (_type) {
		case NATIVE_TYPE::BOOL:
			_data.get().second = static_cast<bool>(_data.get().first);

			return &_data.get().second;
		case NATIVE_TYPE::INT_8:
		case NATIVE_TYPE::INT_16:
		case NATIVE_TYPE::INT_32:
		case NATIVE_TYPE::INT_64:
			return &_data.get().first;
		default:
			break;
		}
	} else {
		switch (_type) {
		case NATIVE_TYPE::BOOL:
			_data.get().second = static_cast<bool>(_data.get().first);

			return &_data.get().second;
		case NATIVE_TYPE::DOUBLE:
			return &_data.get().first;
		default:
			break;
		}
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
inline const void * native_member<Type>::const_native_data(native::NATIVE_TYPE _type) const
{
	// Integral
	if (std::is_same<Type, int64_t>::value) {
		switch (_type) {
		case NATIVE_TYPE::BOOL:
			//_non_zero = static_cast<bool>(_value);

			//return &_non_zero;
		case NATIVE_TYPE::INT_8:
		case NATIVE_TYPE::INT_16:
		case NATIVE_TYPE::INT_32:
		case NATIVE_TYPE::INT_64:
			return &_data.get().first;
		default:
			break;
		}
	} else {
		switch (_type) {
		case NATIVE_TYPE::BOOL:
			//_non_zero = static_cast<bool>(_value);

			//return &_non_zero;
		case NATIVE_TYPE::DOUBLE:
			return &_data.get().first;
		default:
			break;
		}
	}

	throw exception::type_error(BIA_EM_UNSUPPORTED_TYPE);
}

template<typename Type>
template<typename Ty>
inline void native_member<Type>::create_result_member(const Ty & _value, member * _destination)
{
	if (!_destination) {
		_destination = this;
	}

	if (std::is_integral<Ty>::value) {
		_destination->replace_this<int_member>(_value);
	} else {
		_destination->replace_this<double_member>(_value);
	}
}

}
}
}
