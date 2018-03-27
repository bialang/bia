#pragma once

#include <type_traits>

#include "biaMember.hpp"
#include "biaTypeTraits.hpp"
#include "biaException.hpp"
#include "biaNativeOperator.hpp"


namespace bia
{
namespace framework
{
namespace native
{

template<typename T, bool _CONST_REFERENCE, bool _INTEGRAL_REFERENCE>
struct ReferenceOperationChooser
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		p_pDestination->Undefine();

		operation_chooser<T, _RIGHT>::Operation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T & p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		p_left = operation_chooser<T, _RIGHT>::Operation<true>(p_left, p_right, p_unOperator);
	}
};

template<typename T>
struct ReferenceOperationChooser<T, true, true>
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		operation_chooser<T, _RIGHT>::Operation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		operation_chooser<T, _RIGHT>::Operation<false>(p_left, p_right, p_unOperator);
	}
};

template<typename T, bool _CONST_REFERENCE>
struct ReferenceOperationChooser<T, _CONST_REFERENCE, false>
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
	}
};

template<typename T>
using reference_operation_chooser = ReferenceOperationChooser<T, std::is_const<T>::value, std::is_arithmetic<T>::value>;

}
}
}