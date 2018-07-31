#pragma once

#include <limits>
#include <type_traits>
#include <utility>

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

class compile_compare_operation
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
	compile_compare_operation(machine::platform::toolset & _toolset, compiler_value & _value) noexcept : _toolset(_toolset), _value(_value)
	{
	}
	/**
	 * Executes the operator value.
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

		switch (_left.type()) {
		case VT::INT:
			left_constant_operation(_left.value().rt_int, _operator, _right);

			break;
		case VT::DOUBLE:
			left_constant_operation(_left.value().rt_double, _operator, _right);

			break;
		case VT::MEMBER:
			left_member_operation(_left.value().rt_member, _operator, _right);

			break;
		case VT::TEMPORARY_MEMBER:
			left_member_operation(machine::platform::toolset::to_temp_member(_left.value().rt_temp_member), _operator, _right);

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
	 * Executes the compare operator.
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
		using T = machine::platform::toolset;

		switch (_right.type()) {
		case VT::TEST_VALUE_CONSTANT:
			_right.set_return(static_cast<int64_t>(_right.value().rt_test_result));
		case VT::INT:
		{
			if (_right.is_int32()) {
				_toolset.call(&framework::member::test_int32, _member, _operator, static_cast<int32_t>(_right.value().rt_int));
			} else {
				_toolset.call(&framework::member::test_int64, _member, _operator, _right.value().rt_int);
			}

			break;
		}
		case VT::DOUBLE:
			_toolset.call(&framework::member::test_double, _member, _operator, _right.value().rt_double);

			break;
		case VT::MEMBER:
			_toolset.call(&framework::member::test_member, _member, _operator, _right.value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			_toolset.call(&framework::member::test_member, _member, _operator, T::to_temp_member(_right.value().rt_temp_member));

			break;
		case VT::TEST_VALUE_REGISTER:
			_toolset.call(&framework::member::test_int32, _member, _operator, T::test_result_value());

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}

		_value.set_return_test();
		_toolset.write_test();
	}
	/**
	 * Executes the compare operator.
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
		if (std::is_same<typename std::remove_reference<_Left>::type, int64_t>::value) {
			// Is int32
			if (_left <= std::numeric_limits<int32_t>::max() && _left >= std::numeric_limits<int32_t>::min()) {
				_toolset.call(&machine::link::compare_operation_int32, static_cast<int32_t>(_left), _operator, _right);
			} else {
				_toolset.call(&machine::link::compare_operation_int64, _left, _operator, _right);
			}
		} else {
			_toolset.call(&machine::link::compare_operation_double, _left, _operator, _right);
		}

		_value.set_return_test();
		_toolset.write_test();
	}
	/**
	 * Executes the compare operator.
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

		switch (_right.type()) {
		case VT::INT:
			both_constant_operation(std::forward<_Left>(_left), _operator, _right.value().rt_int);

			break;
		case VT::DOUBLE:
			both_constant_operation(std::forward<_Left>(_left), _operator, _right.value().rt_double);

			break;
		case VT::MEMBER:
			left_constant_right_member_operation(std::forward<_Left>(_left), _operator, _right.value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			left_constant_right_member_operation(std::forward<_Left>(_left), _operator, machine::platform::toolset::to_temp_member(_right.value().rt_temp_member));

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
	/**
	 * Executes the compare operator.
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
	void both_constant_operation(_Left && _left, framework::operator_type _operator, _Right && _right)
	{
		using namespace framework;

		switch (_operator) {
		case O_EQUALS:
			_value.set_return(_left == _right);

			break;
		case O_EQUALS_NOT:
			_value.set_return(_left != _right);

			break;
		case O_SAME:
			_value.set_return(std::is_same<_Left, _Right>::value && _left == _right);
			
			break;
		case O_NOT_SAME:
			_value.set_return(!std::is_same<_Left, _Right>::value || _left != _right);

			break;
		case O_LESS_THAN:
			_value.set_return(_left < _right);

			break;
		case O_LESS_EQUALS:
			_value.set_return(_left <= _right);

			break;
		case O_GREATER_THAN:
			_value.set_return(_left > _right);

			break;
		case O_GREATER_EQUALS:
			_value.set_return(_left >= _right);

			break;
		default:
			BIA_COMPILER_DEV_INVALID;
		}
	}
};

}
}