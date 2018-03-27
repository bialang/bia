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

		OperationTypeChooser<std::is_integral<T>::value && std::is_integral<_RIGHT>::value>::ReferenceOperation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T & p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		p_left = OperationTypeChooser<std::is_integral<T>::value && std::is_integral<_RIGHT>::value>::ReferenceOperation<true>(p_left, p_right, p_unOperator);
	}
};

template<typename T>
struct ReferenceOperationChooser<T, true, true>
{
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right, framework::BiaMember * p_pDestination)
	{
		OperationTypeChooser<std::is_integral<T>::value && std::is_integral<_RIGHT>::value>::ReferenceOperation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		OperationTypeChooser<std::is_integral<T>::value && std::is_integral<_RIGHT>::value>::ReferenceOperation<false>(p_left, p_right, p_unOperator);
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
using reference_chooser = ReferenceOperationChooser<T, std::is_const<T>::value, std::is_arithmetic<T>::value>;

}
}
}