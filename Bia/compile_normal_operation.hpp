#pragma once

#include <limits>
#include <type_traits>

#include "exception.hpp"
#include "toolset.hpp"
#include "compiler_value.hpp"
#include "operator.hpp"
#include "operation.hpp"
#include "member.hpp"


namespace bia
{
namespace compiler
{

class compile_normal_operation
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @param [in] _toolset The toolset.
	 * @param [in] _value The compiler value.
	*/
	compile_normal_operation(machine::platform::toolset & _toolset, compiler_value & _value) noexcept : _toolset(_toolset), _value(_value)
	{
	}
	/**
	 * Executes the value.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	*/
	void operate(compiler_value _left, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_left.get_type()) {
		case VT::INT:
			left_constant_operation(_left.get_value().rt_int, _operator, _right);

			break;
		case VT::DOUBLE:
			left_constant_operation(_left.get_value().rt_double, _operator, _right);

			break;
		case VT::MEMBER:
			left_member_operation(_left.get_value().rt_member, _operator, _right);

			break;
		case VT::TEMPORARY_MEMBER:
			left_member_operation(machine::platform::toolset::to_temp_member(_left.get_value().rt_temp_member), _operator, _right);

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}

private:
	/** The toolset. */
	machine::platform::toolset & _toolset;
	/** The compiler value. */
	compiler_value & _value;

	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam _Left The left member value.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	*/
	template<typename _Member>
	void left_member_operation(_Member && _member, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_right.get_type()) {
		case VT::INT:
		{
			if (_right.is_int32()) {
				_toolset.call(&framework::member::operator_call_int32, _member, nullptr, _operator, static_cast<int32_t>(_right.get_value().rt_int));
			} else {
				_toolset.call(&framework::member::operator_call_int32, _member, nullptr, _operator, _right.get_value().rt_int);
			}

			break;
		}
		case VT::DOUBLE:
			_toolset.call(&framework::member::operator_call_double, _member, nullptr, _operator, _right.get_value().rt_double);

			break;
		case VT::MEMBER:
			_toolset.call(&framework::member::operator_call, _member, nullptr, _operator, _right.get_value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			_toolset.call(&framework::member::operator_call, _member, nullptr, _operator, machine::platform::toolset::to_temp_member(_right.get_value().rt_temp_member));

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam _Left Either int64_t or double.
	 * @tparam _Right The right member value.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	*/
	template<typename _Left, typename _Right>
	void left_constant_right_member_operation(_Left && _left, framework::operator_type _operator, _Right && _right)
	{
		if (std::is_same<_Left, int64_t>::value) {
			// Is int32
			if (_left <= std::numeric_limits<int32_t>::max() && _left >= std::numeric_limits<int32_t>::min()) {
				_toolset.call(&machine::link::operation_int32, static_cast<int32_t>(_left), nullptr, _operator, _right);
			} else {
				_toolset.call(&machine::link::operation_int64, _left, nullptr, _operator, _right);
			}
		} else {
			_toolset.call(&machine::link::operation_double, _left, nullptr, _operator, _right);
		}
	}
	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam _Left Either int64_t or double.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	*/
	template<typename _Left>
	void left_constant_operation(_Left && _left, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_right.get_type()) {
		case VT::INT:
			both_constant_operation(_left, _operator, _right.get_value().rt_int);

			break;
		case VT::DOUBLE:
			both_constant_operation(_left, _operator, _right.get_value().rt_double);

			break;
		case VT::MEMBER:
			left_constant_right_member_operation(_left, _operator, _right.get_value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			left_constant_right_member_operation(_left, _operator, machine::platform::toolset::to_temp_member(_right.get_value().rt_temp_member));

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @tparam _Left The type of the left value.
	 * @tparam _Right The type of the right value.
	 *
	 * @param [in] _left The left hand value.
	 * @param _operator The operator.
	 * @param [in] _right The right hand value.
	*/
	template<typename _Left, typename _Right>
	typename std::enable_if<std::is_floating_point<_Left>::value || std::is_floating_point<_Right>::value || true>::type both_constant_operation(_Left && _left, framework::operator_type _operator, _Right && _right)
	{
		using namespace framework;

		switch (_operator) {
		case O_PLUS:
			_value.set_return(_left + _right);

			break;
		case O_MINUS:
			_value.set_return(_left - _right);

			break;
		case O_MULTIPLY:
			_value.set_return(_left * _right);

			break;
		case O_DIVIDE:
			_value.set_return(_left / _right);

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
};

}
}