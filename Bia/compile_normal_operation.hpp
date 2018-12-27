#pragma once

#include <limits>
#include <type_traits>
#include <cmath>

#include "exception.hpp"
#include "toolset.hpp"
#include "compiler_value.hpp"
#include "operator.hpp"
#include "operation.hpp"
#include "member.hpp"
#include "big_int.hpp"


namespace bia
{
namespace compiler
{

/**
 * @brief Helper class for the compiler.
 *
 * Compiles normal operations for the compiler.
 *
 * @see @ref compiler, @ref compile_compare_operation
*/
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
	 *
	 * @throws See left_constant_operation() and left_member_operation().
	*/
	void operate(compiler_value _left, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_left.type()) {
		case VT::INT:
			left_constant_operation(_left.value().rt_int, _operator, _right);

			break;
		case VT::BIG_INT:
			left_constant_operation(*_left.value().rt_big_int, _operator, _right);

			break;
		case VT::DOUBLE:
			left_constant_operation(_left.value().rt_double, _operator, _right);

			break;
		default:
			_left.expand_to_member(nullptr, [&](auto _expanded) {
				if (std::is_same<decltype(_expanded), std::nullptr_t>::value) {
					BIA_IMPLEMENTATION_ERROR;
				}

				left_member_operation(_expanded, _operator, _right);
			});
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
	 * @tparam Member The left member value.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See machine::platform::toolset::call_virtual().
	*/
	template<typename Member>
	void left_member_operation(Member && _member, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		_value.expand_to_member(nullptr, [&](auto _destination) {
			if (std::is_same<decltype(_destination), std::nullptr_t>::value) {
				BIA_IMPLEMENTATION_ERROR;
			}

			switch (_right.type()) {
			case VT::TEST_VALUE_CONSTANT:
				_right.set_return(static_cast<int64_t>(_right.value().rt_test_result));
			case VT::INT:
			{
				if (_right.is_int32()) {
					_toolset.call_virtual(&framework::member::operator_call_int32, _member, _destination, _operator, static_cast<int32_t>(_right.value().rt_int));
				} else {
					_toolset.call_virtual(&framework::member::operator_call_int64, _member, _destination, _operator, _right.value().rt_int);
				}

				break;
			}
			case VT::BIG_INT:
				_toolset.call_virtual(&framework::member::operator_call_big_int, _member, _destination, _operator, _right.value().rt_big_int);

				break;
			case VT::DOUBLE:
				_toolset.call_virtual(&framework::member::operator_call_double, _member, _destination, _operator, _right.value().rt_double);

				break;
			case VT::TEST_VALUE_REGISTER:
				_toolset.call_virtual(&framework::member::operator_call_int32, _member, _destination, _operator, machine::platform::toolset::test_result_value());

				break;
			default:
				_right.expand_to_member(nullptr, [&](auto _expanded) {
					if (std::is_same<decltype(_expanded), std::nullptr_t>::value) {
						BIA_IMPLEMENTATION_ERROR;
					}

					_toolset.call_virtual(&framework::member::operator_call, _member, _destination, _operator, _expanded);
				});
			}
		});
	}
	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam Left Either int64_t or double.
	 * @tparam Right The right member value.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws
	*/
	template<typename Left, typename Right>
	void left_constant_right_member_operation(Left && _left, framework::operator_type _operator, Right && _right)
	{
		BIA_NOT_IMPLEMENTED;

		if (_value.type() != compiler_value::VALUE_TYPE::TEMPORARY_MEMBER) {
			throw;
		}

		auto _destination = machine::platform::toolset::to_temp_member(_value.value().rt_temp_member);

		if (std::is_same<typename std::remove_reference<Left>::type, int64_t>::value) {
			// Is int32
			if (_left <= std::numeric_limits<int32_t>::max() && _left >= std::numeric_limits<int32_t>::min()) {
				_toolset.call_static(&machine::link::operation_int32, _destination, _operator, _right, static_cast<int32_t>(_left));
			} else {
				_toolset.call_static(&machine::link::operation_int64, _destination, _operator, _right, _left);
			}
		} else {
			_toolset.call_static(&machine::link::operation_double, _destination, _operator, _right, _left);
		}
	}
	template<typename Right>
	void left_constant_right_member_operation(dependency::big_int & _left, framework::operator_type _operator, Right && _right)
	{
		BIA_NOT_IMPLEMENTED;
	}
	/**
	 * Executes the operator.
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
	void left_constant_operation(Left && _left, framework::operator_type _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_right.type()) {
		case VT::INT:
			both_constant_operation(_left, _operator, _right.value().rt_int);

			break;
		case VT::BIG_INT:
			both_constant_operation(_left, _operator, *_right.value().rt_big_int);

			break;
		case VT::DOUBLE:
			both_constant_operation(_left, _operator, _right.value().rt_double);

			break;
		case VT::MEMBER:
			left_constant_right_member_operation(_left, _operator, _right.value().rt_member);

			break;
		case VT::TEMPORARY_MEMBER:
			left_constant_right_member_operation(_left, _operator, machine::platform::toolset::to_temp_member(_right.value().rt_temp_member));

			break;
		case VT::LOCAL_MEMBER:
			left_constant_right_member_operation(_left, _operator, machine::platform::toolset::to_local_member(_right.value().rt_local_member));

			break;
		default:
			BIA_IMPLEMENTATION_ERROR;
		}
	}
	/**
	 * Executes the operator.
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
	 *
	 * @throws exception::operator_error The operator is not supported.
	*/
	template<typename Left, typename Right>
	typename std::enable_if<std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value>::type both_constant_operation(Left _left, framework::operator_type _operator, Right _right)
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
		case O_DOUBLE_MULTIPLY:
			_value.set_return(std::pow(_left, _right));

			break;
		case O_DIVIDE:
			_value.set_return(static_cast<int64_t>(_left / _right));

			break;
		case O_DOUBLE_DIVIDE:
			_value.set_return(static_cast<double>(_left) / static_cast<double>(_right));

			break;
		default:
			throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
		}
	}
	template<typename Left, typename Right>
	typename std::enable_if<!(std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value)>::type both_constant_operation(Left _left, framework::operator_type _operator, Right _right)
	{
		BIA_IMPLEMENTATION_ERROR;
	}
	template<typename Right>
	void both_constant_operation(dependency::big_int & _left, framework::operator_type _operator, Right && _right)
	{
		using namespace framework;

		switch (_operator) {
		case O_PLUS:
			_left.add(_right);

			break;
		case O_MINUS:
			_left.subtract(_right);

			break;
		case O_MULTIPLY:
			_left.multiply(_right);

			break;
		case O_DOUBLE_MULTIPLY:
			_left.power(_right);

			break;
		case O_DIVIDE:
			_left.divide(_right);

			break;
		case O_MODULUS:
			_left.modulo(_right);

			break;
		default:
			throw exception::operator_error(BIA_EM_UNSUPPORTED_OPERATOR);
		}

		_value.set_return(&_left);
		free_big_int(_right);
	}
	void free_big_int(const dependency::big_int & _big_int)
	{
		///TODO
	}
	template<typename Type>
	void free_big_int(Type _not_big_int)
	{
	}
};

}
}
