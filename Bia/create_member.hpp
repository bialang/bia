#pragma once

#include <utility>
#include <memory>
#include <type_traits>

#include "type_traits.hpp"
#include "member.hpp"
#include "native_member.hpp"
#include "cstring_member.hpp"
#include "static_function.hpp"
#include "member_function.hpp"
#include "lambda_function.hpp"
#include "raw_class_member.hpp"


namespace bia
{
namespace framework
{

/**
 * Creates the member for a void result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
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
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 21-Apr-18
 *
 * @tparam _Ty An integral type.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The integral value.
 *
 * @throws See member::replace_this().
 */
template<typename _Ty>
inline typename std::enable_if<std::is_integral<_Ty>::value>::type create_member(member * _destination, _Ty _value)
{
	if (_destination) {
		_destination->replace_this<native::int_member>(static_cast<int64_t>(_value));
	}
}

/**
 * Creates the member for a floating point result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 21-Apr-18
 *
 * @tparam _Ty A floating point type.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The floating point value.
 *
 * @throws See member::replace_this().
 */
template<typename _Ty>
inline typename std::enable_if<std::is_floating_point<_Ty>::value>::type create_member(member * _destination, _Ty _value)
{
	if (_destination) {
		_destination->replace_this<native::double_member>(static_cast<double>(_value));
	}
}

/**
 * Creates the member for a C-string result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam _Ty Must be `const char*`.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _value The string.
 *
 * @throws See member::replace_this().
 */
template<typename _Ty>
inline typename std::enable_if<std::is_same<_Ty, const char*>::value>::type create_member(member * _destination, _Ty _value)
{
	if (_destination) {
		_destination->replace_this<native::cstring_member<char>>(_value);
	}
}

/**
 * Creates the member for a static function result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename _Return, typename... _Args>
inline void create_member(member * _destination, _Return(*_function)(_Args...))
{
	if (_destination) {
		_destination->replace_this<executable::static_function<_Return, _Args...>>(_function);
	}
}

/**
 * Creates the member for a member function result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam _Class The class of the function.
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename _Class, typename _Return, typename... _Args>
inline void create_member(member * _destination, _Return(_Class::*_function)(_Args...))
{
	if (_destination) {
		_destination->replace_this<executable::member_function<_Return(_Class::*)(_Args...)>>(_function);
	}
}

/**
 * Creates the member for a member function result.
 *
 * @remarks No checking is performed. Invalid arguments can lead to undefined behavior.
 *
 * @since 3.64.127.716
 * @date 5-May-18
 *
 * @tparam _Class The class of the function.
 * @tparam _Return The return type of the function.
 * @tparam _Args The arguments of the function.
 *
 * @param [in,out] _destination Defines the destination of the member.
 * @param _function The function address.
 *
 * @throws See member::replace_this().
 */
template<typename _Class, typename _Return, typename... _Args>
inline void create_member(member * _destination, _Return(_Class::*_function)(_Args...) const)
{
	if (_destination) {
		_destination->replace_this<executable::member_function<_Return(_Class::*)(_Args...) const>>(_function);
	}
}

template<typename _Ty>
inline typename std::enable_if<utility::negation<std::is_arithmetic<typename std::remove_pointer<typename std::remove_reference<_Ty>::type>::type>::value>::value>::type create_member(member * _destination, _Ty && _value)
{
	if (_destination) {
		_destination->replace_this<object::raw_class_member<typename std::remove_reference<_Ty>::type>>(std::move(_value));
	}
}

template<typename _Ty>
inline typename std::enable_if<utility::negation<std::is_arithmetic<typename std::remove_pointer<typename std::remove_reference<_Ty>::type>::type>::value>::value>::type create_member(member * _destination, const _Ty & _value)
{
	if (_destination) {
		_destination->replace_this<object::raw_class_member<typename std::remove_reference<_Ty>::type>>(_value);
	}
}

}
}