#pragma once

#include <limits>
#include <type_traits>
#include <utility>

#include "exception.hpp"
#include "virtual_translator.hpp"
#include "compiler_value.hpp"
#include "operator.hpp"
#include "operation.hpp"
#include "member.hpp"


namespace bia
{
namespace compiler
{

/**
 * @brief Helper class for the compiler.
 *
 * Compiles compare operations for the compiler.
 *
 * @see @ref compiler, @ref compile_normal_operation
*/
class compile_compare_operation
{
public:
	/**
	 * Constructor.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @param [in] _translator The translator.
	 * @param [in] _value The compiler value.
	*/
	compile_compare_operation(machine::virtual_machine::virtual_translator & _translator, compiler_value & _value) noexcept : _translator(_translator), _value(_value)
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
	 *
	 * @throws See left_constant_operation() and left_member_operation().
	 * @throws See compiler_value::expand_to_member().
	*/
	void operate(compiler_value _left, framework::operator_t _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		_left.expand_to_member(_translator, [&](auto _member) {
			if (std::is_same<decltype(_member), machine::virtual_machine::invalid_index>::value) {
				switch (_left.type()) {
				case VT::INT:
					left_constant_operation(_left.value().rt_int, _operator, _right);

					break;
				case VT::DOUBLE:
					left_constant_operation(_left.value().rt_double, _operator, _right);

					break;
				default:
					BIA_IMPLEMENTATION_ERROR;
				}
			} else {
				left_member_operation(_member, _operator, _right);
			}
		});
	}

private:
	/** The translator. */
	machine::virtual_machine::virtual_translator & _translator;
	/** The compiler value. */
	compiler_value & _value;

	/**
	 * Executes the compare operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See machine::platform::toolset::call().
	*/
	void left_member_operation(const machine::virtual_machine::index & _member, framework::operator_t _operator, compiler_value _right)
	{
		_right.expand_to_member(_translator, [&](auto _right_member) {
			if (std::is_same<decltype(_right_member), machine::virtual_machine::invalid_index>::value) {
				_translator.test_call_immediate(_member, _operator, _right.value().rt_int);
				//BIA_NOT_IMPLEMENTED;
			} else {
				_translator.test_call(_member, _operator, _right_member);
			}
		});

		/*
		using VT = compiler_value::VALUE_TYPE;
		using T = machine::platform::toolset;

		switch (_right.type()) {
		case VT::TEST_VALUE_CONSTANT:
			_right.set_return(static_cast<int64_t>(_right.value().rt_test_result));
		case VT::INT:
		{
			if (_right.is_int32()) {
				_toolset.call_virtual(&framework::member::test_int32, _member, _operator, static_cast<int32_t>(_right.value().rt_int));
			} else {
				_toolset.call_virtual(&framework::member::test_int64, _member, _operator, _right.value().rt_int);
			}

			break;
		}
		case VT::DOUBLE:
			_toolset.call_virtual(&framework::member::test_double, _member, _operator, _right.value().rt_double);

			break;
		case VT::MEMBER:
			_toolset.call_virtual(&framework::member::test_member, _member, _operator, _right.value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			_toolset.call_virtual(&framework::member::test_member, _member, _operator, T::to_temp_member(_right.value().rt_temp_member));

			break;
		case VT::TEST_VALUE_REGISTER:
			_toolset.call_virtual(&framework::member::test_int32, _member, _operator, T::test_result_value());

			break;
		default:
			BIA_IMPLEMENTATION_ERROR;
		}*/

		_value.set_return_test();
	}
	/**
	 * Executes the compare operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam Left Either int64_t or double.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See machine::platform::toolset::call().
	*/
	template<typename Left>
	void left_constant_right_member_operation(Left && _left, framework::operator_t _operator, const machine::virtual_machine::index & _right)
	{
		BIA_NOT_IMPLEMENTED;
		/*if (std::is_same<typename std::remove_reference<Left>::type, int64_t>::value) {
			// Is int32
			if (_left <= std::numeric_limits<int32_t>::max() && _left >= std::numeric_limits<int32_t>::min()) {
				_toolset.call_static(&machine::link::compare_operation_int32, _operator, _right, static_cast<int32_t>(_left));
			} else {
				_toolset.call_static(&machine::link::compare_operation_int64, _operator, _right, _left);
			}
		} else {
			_toolset.call_static(&machine::link::compare_operation_double, _operator, _right, _left);
		}

		_value.set_return_test();*/
	}
	/**
	 * Executes the compare operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam Left Either int64_t or double.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See left_constant_right_member_operation().
	*/
	template<typename Left>
	void left_constant_operation(Left && _left, framework::operator_t _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		_right.expand_to_member(_translator, [&](auto _right_member) {
			if (std::is_same<decltype(_right_member), machine::virtual_machine::invalid_index>::value) {
				switch (_right.type()) {
				case VT::INT:
					both_constant_operation(std::forward<Left>(_left), _operator, _right.value().rt_int);

					break;
				case VT::DOUBLE:
					both_constant_operation(std::forward<Left>(_left), _operator, _right.value().rt_double);

					break;
				default:
					BIA_IMPLEMENTATION_ERROR;
				}
			} else {
				left_constant_right_member_operation(std::forward<Left>(_left), _operator, _right_member);
			}
		});
		
	}
	/**
	 * Executes the compare operator.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @tparam Left The type of the left value.
	 * @tparam Right The type of the right value.
	 *
	 * @param [in] _left The left hand value.
	 * @param _operator The operator.
	 * @param [in] _right The right hand value.
	*/
	template<typename Left, typename Right>
	void both_constant_operation(Left && _left, framework::operator_t _operator, Right && _right)
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
			_value.set_return(std::is_same<Left, Right>::value && _left == _right);

			break;
		case O_NOT_SAME:
			_value.set_return(!std::is_same<Left, Right>::value || _left != _right);

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
			BIA_IMPLEMENTATION_ERROR;
		}
	}
};

}
}
