#pragma once

#include <utility>
#include <type_traits>

#include "biaMember.hpp"
#include "biaInt.hpp"
#include "biaFloat.hpp"
#include "biaDouble.hpp"
#include "biaCString.h"
#include "biaStaticFunction.hpp"
#include "biaClassRaw.hpp"


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
		p_pDestination->ReplaceObject<native::BiaInt>(std::forward<T>(p_value));
	//Float
	else if (std::is_same<T, float>::value)
		p_pDestination->ReplaceObject<native::BiaFloat>(std::forward<T>(p_value));
	//Double
	else if (std::is_same<T, double>::value)
		p_pDestination->ReplaceObject<native::BiaDouble>(std::forward<T>(p_value));
	//CString
	else if (std::is_same<T, const char*>::value)
		p_pDestination->ReplaceObject<native::BiaCString>(std::forward<T>(p_value));
	//Static function
	else if (std::is_pointer<T>::value && std::is_function<std::remove_pointer<T>::type>::value)
		;// p_pDestination->ReplaceObject<executable::BiaStaticFunction<std::add_pointer<std::remove_pointer<_TYPE>::type>::type>>(std::forward<T>(p_value));
	//Wrap into raw class
	else
		p_pDestination->ReplaceObject<object::BiaClassRaw<_TYPE>>(std::shared_ptr<_TYPE>(new _TYPE(std::forward<T>(p_value))));
		//throw BIA_IMPLEMENTATION_EXCEPTION("Value not supported.");
}

}
}