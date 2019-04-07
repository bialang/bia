#pragma once

#include <limits>
#include <type_traits>
#include <cmath>

#include "exception.hpp"
#include "virtual_translator.hpp"
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
	 * @param [in] _translator The translator.
	 * @param [in] _value The compiler value.
	*/
	compile_normal_operation(machine::virtual_machine::virtual_translator & _translator, compiler_value & _value) noexcept : _translator(_translator), _value(_value)
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
	 * @throws See compiler_value::expand_to_member().
	*/
	void operate(compiler_value _left, framework::operator_t _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		switch (_left.type()) {
		case VT::INT:
			left_constant_operation(_left.value().rt_int, _operator, _right);

			break;
		case VT::DOUBLE:
			left_constant_operation(_left.value().rt_double, _operator, _right);

			break;
		default:
			_left.expand_to_member(_translator, [&](auto _expanded) {
				if (std::is_same<decltype(_expanded), machine::virtual_machine::invalid_index>::value) {
					BIA_IMPLEMENTATION_ERROR;
				} else {
					this->left_member_operation(_expanded, _operator, _right);
				}
			});
		}
	}

private:
	/** The translator. */
	machine::virtual_machine::virtual_translator & _translator;
	/** The compiler value. */
	compiler_value & _value;

	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @param _member The left member.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See machine::virtual_machine::virtual_translator::operator_call() and machine::virtual_machine::virtual_translator::operator_call_immediate().
	 * @throws See compiler_value::expand_to_member().
	*/
	void left_member_operation(const machine::virtual_machine::index & _member, framework::operator_t _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		_value.expand_to_member(_translator, [&](auto _destination) {
			auto _dest = &_destination;

			// Destination is calling member
			if (std::is_same<decltype(_destination), machine::virtual_machine::invalid_index>::value) {
				_dest = nullptr;
			}

			_right.expand_to_member(_translator, [&](auto _expanded) {
				if (std::is_same<decltype(_expanded), machine::virtual_machine::invalid_index>::value) {
					switch (_right.type()) {
					case VT::INT:
						_translator.operator_call_immediate(_member, _dest, _operator, _right.value().rt_int);

						break;
					case VT::DOUBLE:
						_translator.operator_call_immediate(_member, _dest, _operator, _right.value().rt_double);

						break;
					default:
						BIA_IMPLEMENTATION_ERROR;
					}
				} else {
					_translator.operator_call(_member, _dest, _operator, _expanded);
				}
			});
		});
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
	 * @param _right The right member.
	 *
	 * @throws See machine::virtual_machine::virtual_translator::operator_call_immediate_reverse().
	 * @throws See compiler_value::expand_to_member().
	*/
	template<typename Left>
	void left_constant_right_member_operation(Left _left, framework::operator_t _operator, const machine::virtual_machine::index & _right)
	{
		_value.expand_to_member(_translator, [&](auto _expanded) {
			auto _destination = &_expanded;

			// No destination
			if (std::is_same<decltype(_expanded), machine::virtual_machine::invalid_index>::value) {
				_destination = nullptr;
			}

			_translator.operator_call_immediate_reverse(_right, _destination, _operator, _left);
		});
	}
	/**
	 * Executes the operator.
	 *
	 * @since 3.64.131.726
	 * @date 14-Jun-18
	 *
	 * @tparam Left The left constant type.
	 *
	 * @param _left The left hand value.
	 * @param _operator The operator.
	 * @param _right The right hand value.
	 *
	 * @throws See left_constant_right_member_operation() and both_constant_operation().
	 * @throws See compiler_value::expand_to_member().
	*/
	template<typename Left>
	void left_constant_operation(Left && _left, framework::operator_t _operator, compiler_value _right)
	{
		using VT = compiler_value::VALUE_TYPE;

		_right.expand_to_member(_translator, [&](auto _expanded) {
			if (std::is_same<decltype(_expanded), machine::virtual_machine::invalid_index>::value) {
				switch (_right.type()) {
				case VT::INT:
					both_constant_operation(_left, _operator, _right.value().rt_int);

					break;
				case VT::DOUBLE:
					both_constant_operation(_left, _operator, _right.value().rt_double);

					break;
				default:
					BIA_IMPLEMENTATION_ERROR;
				}
			} else {
				left_constant_right_member_operation(_left, _operator, _expanded);
			}
		});
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
	typename std::enable_if<std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value>::type both_constant_operation(Left _left, framework::operator_t _operator, Right _right)
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
	typename std::enable_if<!(std::is_arithmetic<Left>::value && std::is_arithmetic<Right>::value)>::type both_constant_operation(Left _left, framework::operator_t _operator, Right _right)
	{
		BIA_IMPLEMENTATION_ERROR;
	}
	template<typename Right>
	void both_constant_operation(detail::big_int & _left, framework::operator_t _operator, Right && _right)
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
	void free_big_int(const detail::big_int & _big_int)
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
