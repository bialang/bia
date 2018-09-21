#pragma once

#include <type_traits>

#include "type_traits.hpp"
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
class native_member final : public native_variable
{
public:
	typedef native_member<int64_t> int_member;
	typedef native_member<double> double_member;

	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _value The initial value.
	 *
	 * @throws See utility::share::share().
	*/
	native_member(typename std::enable_if<std::is_same<Type, int64_t>::value || std::is_same<Type, double>::value, Type>::type _value) : _data(_value, false)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _data The data of the referred object.
	*/
	native_member(const utility::share<std::pair<Type, bool>> & _data) noexcept : _data(_data)
	{
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const override
	{
		machine::link::print(_data.get().first);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) override
	{
		create_result_member(_data.get().first, _destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) override
	{
		_destination->replace_this<native_member<Type>>(_data);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) override
	{
		copy(_destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		if (std::is_same<Type, int64_t>::value) {
			create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right->to_int()), _destination);
		} else {
			create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right->to_double()), _destination);
		}
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) override
	{
		create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) override
	{
		create_result_member(operation_chooser_l<Type>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) override
	{
		BIA_NOT_IMPLEMENTED;
	}
	virtual int flags() const override
	{
		return F_TO_INT | F_TO_DOUBLE | (std::is_same<Type, int64_t>::value ? F_INT : F_DOUBLE);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const override
	{
		return native::test(_data.get().first);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const override
	{
		if (std::is_same<Type, int64_t>::value) {
			return test_operation(_data.get().first, _operator, _right->to_int());
		} else {
			return test_operation(_data.get().first, _operator, _right->to_double());
		}
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const override
	{
		return test_operation(_data.get().first, _operator, _right);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const override
	{
		return test_operation(_data.get().first, _operator, _right);
	}
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const override
	{
		return test_operation(_data.get().first, _operator, _right);
	}
	virtual int64_t to_int() const override
	{
		return static_cast<int64_t>(_data.get().first);
	}
	virtual double to_double() const override
	{
		return static_cast<double>(_data.get().first);
	}

protected:
	virtual void * native_data(native::NATIVE_TYPE _type) override
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
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const override
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

private:
	utility::share<std::pair<Type, bool>> _data;
	/** The arithmetic value of type: int64_t, float or double. */
	//mutable bool _non_zero;
	//Type _value;
	/** True if the value is non zero. */

	template<typename _T>
	void create_result_member(const _T & _value, member * _destination)
	{
		if (!_destination) {
			_destination = this;
		}

		if (std::is_integral<_T>::value) {
			_destination->replace_this<int_member>(_value);
		} else {
			_destination->replace_this<double_member>(_value);
		}
	}
};

using int_member = native_member<int64_t>;
using double_member = native_member<double>;

}
}
}
