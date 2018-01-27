#pragma once

#include <cstdarg>
#include <cstdint>

#include "biaMember.hpp"


namespace bia
{
namespace force
{

template<typename _RETURN, typename... _ARGS>
inline bool DisguisedCall(_RETURN(*p_pFunction)(_ARGS...), void * p_pDestination, uint32_t p_unCount, va_list & p_args)
{
	//Invalid count of arguments
	if (p_unCount != sizeof...(_ARGS))
		return false;

	//Call
	//p_pFunction((*va_arg(p_args, framework::BiaMember*)->Cast<_ARGS>())...);
	p_pFunction(*va_arg(p_args, framework::BiaMember*)->Cast<int>(), *va_arg(p_args, framework::BiaMember*)->Cast<int>());

	return true;
}

}
}