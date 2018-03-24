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

template<typename _RIGHT>
inline typename utility::NativeOperationResult<int32_t, _RIGHT>::type ArithmeticReference(int32_t p_nLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation(p_nLeft, p_right, p_unOperator);
}

template<typename _RIGHT>
inline typename utility::NativeOperationResult<int64_t, _RIGHT>::type ArithmeticReference(int64_t p_llLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation(p_llLeft, p_right, p_unOperator);
}

template<typename _RIGHT>
inline typename utility::NativeOperationResult<float, _RIGHT>::type ArithmeticReference(float p_rLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation(p_rLeft, p_right, p_unOperator);
}

template<typename _RIGHT>
inline typename utility::NativeOperationResult<double, _RIGHT>::type ArithmeticReference(double p_rLeft, _RIGHT p_right, uint32_t p_unOperator)
{
	return ArithmeticOperation(p_rLeft, p_right, p_unOperator);
}

template<typename _LEFT, typename _RIGHT>
inline typename std::enable_if<std::is_arithmetic<_LEFT>::value && std::is_arithmetic<_RIGHT>::value, typename utility::NativeOperationResult<_LEFT, _RIGHT>::type>::type ArithmeticReferenceOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	typedef typename utility::IntegralPromoter<_LEFT, std::is_integral<_LEFT>::value, sizeof(_LEFT)>::type type;

	return ArithmeticReference(static_cast<type>(p_left), p_right, p_unOperator);
}

template<typename _LEFT, typename _RIGHT>
inline typename std::enable_if<utility::Negation<std::is_arithmetic<_LEFT>::value && std::is_arithmetic<_RIGHT>::value>::value>::type ArithmeticReferenceOperation(_LEFT p_left, _RIGHT p_right, uint32_t p_unOperator)
{
	throw BIA_IMPLEMENTATION_EXCEPTION("Should not have happened.");
}

}
}
}