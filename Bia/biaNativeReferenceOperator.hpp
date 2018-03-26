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

template<bool _ALLOW_ASSIGN, typename _RIGHT>
inline typename utility::NativeOperationResult<int32_t, _RIGHT>::type ArithmeticReference(int32_t p_nLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation<_ALLOW_ASSIGN>(p_nLeft, p_right, p_unOperator);
}

template<bool _ALLOW_ASSIGN, typename _RIGHT>
inline typename utility::NativeOperationResult<int64_t, _RIGHT>::type ArithmeticReference(int64_t p_llLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation<_ALLOW_ASSIGN>(p_llLeft, p_right, p_unOperator);
}

template<bool _ALLOW_ASSIGN, typename _RIGHT>
inline typename utility::NativeOperationResult<float, _RIGHT>::type ArithmeticReference(float p_rLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation<_ALLOW_ASSIGN>(p_rLeft, p_right, p_unOperator);
}

template<bool _ALLOW_ASSIGN, typename _RIGHT>
inline typename utility::NativeOperationResult<double, _RIGHT>::type ArithmeticReference(double p_rLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation<_ALLOW_ASSIGN>(p_rLeft, p_right, p_unOperator);
}

template<bool _ALLOW_ASSIGN, typename _LEFT, typename _RIGHT>
inline typename utility::NativeOperationResult<_LEFT, _RIGHT>::type ArithmeticReferenceOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	typedef typename utility::NativeTypeAdapter<_LEFT, std::is_integral<_LEFT>::value, sizeof(_LEFT)>::type type;

	return ArithmeticReference<_ALLOW_ASSIGN>(static_cast<type>(p_left), p_right, p_unOperator);
}

template<typename T, bool _CONST_REFERENCE, bool _INTEGRAL_REFERENCE>
struct ReferenceOperationChooser
{
	template<typename _RIGHT>
	inline static void Operation(framework::BiaMember * p_pDestination, T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		p_pDestination->Undefine();

		ArithmeticReferenceOperation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T & p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		p_left = ArithmeticReferenceOperation<true>(p_left, p_right, p_unOperator);
	}
};

template<typename T>
struct ReferenceOperationChooser<T, true, true>
{
	template<typename _RIGHT>
	inline static void Operation(framework::BiaMember * p_pDestination, T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		ArithmeticReferenceOperation<false>(p_left, p_right, p_unOperator);
	}
	template<typename _RIGHT>
	inline static void Operation(T p_left, uint32_t p_unOperator, _RIGHT p_right)
	{
		ArithmeticReferenceOperation<false>(p_left, p_right, p_unOperator);
	}
};

template<typename T, bool _CONST_REFERENCE>
struct ReferenceOperationChooser<T, _CONST_REFERENCE, false>
{
	template<typename _RIGHT>
	inline static void Operation(framework::BiaMember * p_pDestination, T p_left, uint32_t p_unOperator, _RIGHT p_right)
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