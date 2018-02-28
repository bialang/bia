#pragma once

#include <utility>
#include <type_traits>

#include "biaMember.hpp"
#include "biaInt.hpp"
#include "biaStaticFunction.hpp"


namespace bia
{
namespace framework
{

inline void MemberCreator(BiaMember * p_pDestination)
{
	p_pDestination->Undefine();
}

template<typename T>
inline void MemberCreator(BiaMember * p_pDestination, T && p_value)
{
	using _TYPE = std::remove_reference<T>::type;

	//Integral type
	if (std::is_integral<T>::value)
		p_pDestination->ReplaceObject<BiaInt>(std::forward<T>(p_value));
	//Static function
	else if (std::is_pointer<T>::value && std::is_function<std::remove_pointer<T>::type>::value)
		;// p_pDestination->ReplaceObject<executable::BiaStaticFunction<std::add_pointer<std::remove_pointer<_TYPE>::type>::type>>(std::forward<T>(p_value));
	else
		throw BIA_IMPLEMENTATION_EXCEPTION("Value not supported.");
}

}
}