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

	//Destroy destination
	p_pDestination->~BiaMember();

	//Integral type
	if (std::is_integral<T>::value)
		new(p_pDestination) BiaInt(std::forward<T>(p_value));
	else
		throw BIA_IMPLEMENTATION_EXCEPTION("Value not supported.");
}

}
}