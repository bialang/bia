#pragma once

#include <type_traits>

#include "type_traits.hpp"
#include "native_variable.hpp"
#include "exception.hpp"
#include "native_operator.hpp"
#include "native_test_operator.hpp"
#include "print.hpp"
#include "share.hpp"
#include "machine_context.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename _Ty>
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
	 * @throws See @ref utility::share::share().
	*/
	native_member(typename std::enable_if<std::is_same<_Ty, int64_t>::value || std::is_same<_Ty, double>::value, _Ty>::type _value) : _data(_value, false)
	{
	}
	/**
	 * Refer-Constructor.
	 *
	 * @since 3.64.132.730
	 * @date 16-Jun-18
	 *
	 * @param _data The data of the referred class.
	*/
	native_member(const utility::share<std::pair<_Ty, bool>> & _data) noexcept : _data(_data)
	{
	}
	virtual void print() const override
	{
		machine::link::print(_data.get().first);
	}
	virtual void copy(member * _destination) override
	{
		create_result_member(_data.get().first, _destination);
	}
	virtual void refer(member * _destination) override
	{
		_destination->replace_this<native_member<_Ty>>(_data);
	}
	virtual void clone(member * _destination) override
	{
		copy(_destination);
	}
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) override
	{
		if (std::is_same<_Ty, int64_t>::value) {
			create_result_member(operation_chooser_l<_Ty>::operate_result(_data.get().first, _operator, _right->to_int()), _destination);
		} else {
			create_result_member(operation_chooser_l<_Ty>::operate_result(_data.get().first, _operator, _right->to_double()), _destination);
		}
	}
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) override
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right)
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right)
	{
		create_result_member(operation_chooser_l<_Ty>::operate_result(_data.get().first, _operator, _right), _destination);
	}
	virtual int flags() const override
	{
		return F_NONE;
	}
	virtual int32_t test() const override
	{
		return native::test(_data.get().first);
	}
	virtual int32_t test_member(operator_type _operator, member * _right) const override
	{
		if (std::is_same<_Ty, int64_t>::value) {
			return test_operation(_data.get().first, _operator, _right->to_int());
		} else {
			return test_operation(_data.get().first, _operator, _right->to_double());
		}
	}
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const override
	{
		return test_operation(_data.get().first, _operator, _right);
	}
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const override
	{
		return test_operation(_data.get().first, _operator, _right);
	}
	virtual int32_t test_double(operator_type _operator, double _right) const override
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
		if (std::is_same<_Ty, int64_t>::value) {
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
		if (std::is_same<_Ty, int64_t>::value) {
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
	utility::share<std::pair<_Ty, bool>> _data;
	/** The arithmetic value of type: int64_t, float or double. */
	//mutable bool _non_zero;
	//_Ty _value;
	/** True if the value is non zero. */

	template<typename _T>
	void create_result_member(_T && _value, member * _destination)
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