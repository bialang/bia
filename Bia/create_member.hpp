#pragma once

#include <utility>
#include <memory>
#include <type_traits>

#include "type_traits.hpp"
#include "member.hpp"
#include "big_int_member.hpp"
#include "double_member.hpp"
#include "cstring_member.hpp"
#include "static_function.hpp"
#include "member_function.hpp"
#include "lambda_function.hpp"
#include "raw_object.hpp"
#include "string_manager.hpp"


namespace bia
{
namespace framework
{

/**
 * Creates the member for a void result.
 *
 * @since 3.64.127.716
 * @date 8-Apr-18
 *
 * @param [in,out] _destination Defines the destination of the member.
 */
inline void create_member(member * _destination) noexcept
{
	if (_destination) {
		_destination->undefine();
	}
}

/**
 * Creates the member for an integral result.
 *
 * @since 3.64.127.716
 * @date 21-Apr-18
 *
 * @tparam Type An integral type.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The integral value.
 *
 * @throws See member::replace_this().
 */
template<typename Type>
inline typename std::enable_if<std::is_integral<Type>::value>::type create_member(member * _destination, Type _value)
{
	if (_destination) {
		_destination->template replace_this<native::big_int_member>(_value);
	}
}

/**
 * Creates the member for a floating point result.
 *
 * @since 3.64.127.716
 * @date 21-Apr-18
 *
 * @tparam Type A floating point type.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The floating point value.
 *
 * @throws See member::replace_this().
 */
template<typename Type>
inline typename std::enable_if<std::is_floating_point<Type>::value>::type create_member(member * _destination, Type _value)
{
	if (_destination) {
		_destination->template replace_this<native::double_member>(static_cast<double>(_value));
	}
}

/**
 * Creates the member for a C-string result.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam Type Must be `const char*`.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The string.
 *
 * @throws See member::replace_this().
 */
template<typename Type>
inline typename std::enable_if<std::is_same<Type, const char*>::value>::type create_member(member * _destination, Type _value)
{
	if (_destination) {
		_destination->template replace_this<native::cstring_member<char>>(_value);
	}
}

template<typename Char_type>
inline void create_member(member * _destination, machine::string_manager::string_wrapper<Char_type> _string)
{
	if (_destination) {
		_destination->template replace_this<native::cstring_member<Char_type>>(_string);
	}
}

/**
 * Creates the member for a static function result.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam Return The return type of the function.
 * @tparam Arguments The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename Return, typename... Arguments>
inline void create_member(member * _destination, Return(*_function)(Arguments...))
{
	if (_destination) {
		_destination->template replace_this<executable::static_function<0, Return, Arguments...>>(_function);
	}
}

/**
 * Creates the member for a member function result.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam Class The class of the function.
 * @tparam Return The return type of the function.
 * @tparam Arguments The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename Class, typename Return, typename... Arguments>
inline void create_member(member * _destination, Return(Class::*_function)(Arguments...))
{
	if (_destination) {
		_destination->template replace_this<executable::member_function<0, Return(Class::*)(Arguments...)>>(_function);
	}
}

/**
 * Creates the member for a member function result.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam Class The class of the function.
 * @tparam Return The return type of the function.
 * @tparam Arguments The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename Class, typename Return, typename... Arguments>
inline void create_member(member * _destination, Return(Class::*_function)(Arguments...) const)
{
	if (_destination) {
		_destination->template replace_this<executable::member_function<0, Return(Class::*)(Arguments...) const>>(_function);
	}
}

template<typename Type>
inline typename std::enable_if<utility::negation<std::is_arithmetic<typename std::remove_pointer<typename std::remove_reference<Type>::type>::type>::value>::value>::type create_member(member * _destination, Type && _value)
{
	if (_destination) {
		_destination->template replace_this<object::raw_object<typename std::remove_reference<Type>::type>>(std::move(_value));
	}
}

template<typename Type>
inline typename std::enable_if<utility::negation<std::is_arithmetic<typename std::remove_pointer<typename std::remove_reference<Type>::type>::type>::value>::value>::type create_member(member * _destination, const Type & _value)
{
	if (_destination) {
		_destination->template replace_this<object::raw_object<typename std::remove_reference<Type>::type>>(_value);
	}
}

}
}
