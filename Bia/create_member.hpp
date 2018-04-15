#pragma once

#include <utility>
#include <type_traits>

#include "member.hpp"
#include "biaNative.hpp"
#include "biaNativeReference.hpp"
#include "biaCString.hpp"
#include "biaStaticFunction.hpp"
#include "biaClassRaw.hpp"


namespace bia
{
namespace framework
{

/**
 * Creates the member for a void result.
 *
 * @since	3.64.127.716
 * @date	8-Apr-18
 *
 * @param	[in,out]	_destination	Defines the destination of the member.
 */
inline void create_member(member * _destination) noexcept
{
	_destination->undefine();
}

template<typename _Ty>
inline typename std::enable_if<std::is_integral<_Ty>::value>::type create_member(member * _destination, _Ty && _value)
{
	_destination->replace_this<native::BiaInt>(_value);
}

template<typename _Ty>
inline typename std::enable_if<std::is_floating_point<_Ty>::value>::type MemberCreator(BiaMember * p_pDestination, _Ty p_value)
{
	p_pDestination->ReplaceObject<native::BiaNative<_Ty>>(p_value);
}

template<typename _Ty>
inline typename std::enable_if<std::is_arithmetic<_Ty>::value && bia::utility::Negation<std::is_same<_Ty, const char>::value>::value>::type MemberCreator(BiaMember * p_pDestination, _Ty * p_pValue)
{
	p_pDestination->ReplaceObject<native::BiaNativeReference<_Ty>>(p_value);
}

template<typename _Ty>
inline typename std::enable_if<std::is_arithmetic<_Ty>::value>::type MemberCreator(BiaMember * p_pDestination, _Ty & p_value)
{
	p_pDestination->ReplaceObject<native::BiaNativeReference<_Ty>>(p_value);
}

template<typename _Ty>
inline typename std::enable_if<std::is_same<_Ty, const char*>::value>::type MemberCreator(BiaMember * p_pDestination, _Ty p_value)
{
	p_pDestination->ReplaceObject<native::BiaCString>(p_value);
}

template<typename _RETURN, typename... _ARGS>
inline void MemberCreator(BiaMember * p_pDestination, _RETURN(*p_value)(_ARGS...))
{
	p_pDestination->ReplaceObject<executable::BiaStaticFunction<_RETURN, _ARGS...>>(p_value);
}

template<typename _Ty>
inline typename std::enable_if<bia::utility::Negation<std::is_arithmetic<typename std::remove_pointer<typename std::remove_reference<_Ty>::type>::type>::value>::value>::type MemberCreator(BiaMember * p_pDestination, _Ty && p_value)
{
	using _TYPE = typename std::remove_reference<_Ty>::type;

	p_pDestination->ReplaceObject<object::BiaClassRaw<_TYPE>>(std::shared_ptr<_TYPE>(new _TYPE(std::forward<_Ty>(p_value))));
}

}
}