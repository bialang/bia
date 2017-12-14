#pragma once

#include "biaMember.h"
#include "biaType.h"
#include "biaMemberHolder.h"


namespace bia
{
namespace api
{
namespace framework
{
namespace native
{

template<typename T>
class BiaNativeVariable
{
	BiaNativeVariable()
	{
		static_assert(false, "Invalid native variable type.");
	}
};

template<typename _RETURN, _RETURN _S_RETURN, _RETURN _F_RETURN, typename T>
inline _RETURN NativeHelper(T && p_function, BiaMember * p_pRight)
{
	switch (p_pRight->GetFlags() & BiaMember::F_NATIVE_TYPE_MASK)
	{
	case BiaMember::F_NATIVE_LONG:
	{
		long long * pllRight;

		if (p_pRight->Cast<long long>(pllRight))
		{
			p_function(*pllRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_INT:
	{
		int * pnRight;

		if (p_pRight->Cast<int>(pnRight))
		{
			p_function(*pnRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_SHORT:
	{
		short * psRight;

		if (p_pRight->Cast<short>(psRight))
		{
			p_function(*psRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_BYTE:
	{
		char * pcRight;

		if (p_pRight->Cast<char>(pcRight))
		{
			p_function(*pcRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_DOUBLE:
	{
		double * prRight;

		if (p_pRight->Cast<double>(prRight))
		{
			p_function(*prRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_FLOAT:
	{
		float * prRight;

		if (p_pRight->Cast<float>(prRight))
		{
			p_function(*prRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	default:
		return _F_RETURN;
	}
}

template<typename _RETURN, _RETURN _S_RETURN, _RETURN _F_RETURN, typename T>
inline _RETURN NativeHelperIntegral(T && p_function, BiaMember * p_pRight)
{
	switch (p_pRight->GetFlags() & BiaMember::F_NATIVE_TYPE_MASK)
	{
	case BiaMember::F_NATIVE_LONG:
	{
		long long * pllRight;

		if (p_pRight->Cast<long long>(pllRight))
		{
			p_function(*pllRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_INT:
	{
		int * pnRight;

		if (p_pRight->Cast<int>(pnRight))
		{
			p_function(*pnRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_SHORT:
	{
		short * psRight;

		if (p_pRight->Cast<short>(psRight))
		{
			p_function(*psRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	case BiaMember::F_NATIVE_BYTE:
	{
		char * pcRight;

		if (p_pRight->Cast<char>(pcRight))
		{
			p_function(*pcRight);

			return _S_RETURN;
		}

		return _F_RETURN;
	}
	default:
		return _F_RETURN;
	}
}

template<typename T>
inline int NativeOperatorHelperFloat(unsigned int p_uiOperator, T & p_data, void * p_pDestination, BiaMember * p_pRight)
{
	switch (p_uiOperator)
	{
	case BiaMember::O_PLUS:
		return NativeHelper<int, 1, -1>([&](auto p_right) {
			auto result = p_data + p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_MINUS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data - p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_DIVIDE:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data / p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_MULTIPLY:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data * p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_ASSIGN_PLUS:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data + p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_MINUS:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data - p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_DIVIDE:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data / p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_MULTIPLY:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data * p_right); }, p_pRight);

	case BiaMember::O_MODULUS:
	case BiaMember::O_ASSIGN_MODULUS:
	case BiaMember::O_BITWISE_OR:
	case BiaMember::O_BITWISE_AND:
	case BiaMember::O_BITWISE_XOR:
	case BiaMember::O_BITWISE_ARITHMETIC_LEFT_SHIFT:
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_OR:
	case BiaMember::O_BITWISE_ASSIGN_AND:
	case BiaMember::O_BITWISE_ASSIGN_XOR:
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		break;

	case BiaMember::O_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data == p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_EQUALS_NOT:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data != p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_LESS_THAN:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data < p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_LESS_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data <= p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_GREATER_THAN:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data > p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_GREATER_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data >= p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	default:
		break;
	}

	return -1;
}

template<typename T>
inline int NativeOperatorHelperIntegral(unsigned int p_uiOperator, T & p_data, void * p_pDestination, BiaMember * p_pRight)
{
	switch (p_uiOperator)
	{
	case BiaMember::O_PLUS:
		return NativeHelper<int, 1, -1>([&](auto p_right) {
			auto result = p_data + p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_MINUS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data - p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_DIVIDE:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data / p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_MULTIPLY:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data * p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_MODULUS:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data % p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_ASSIGN_PLUS:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data + p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_MINUS:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data - p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_DIVIDE:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data / p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_MULTIPLY:
		return NativeHelper<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data * p_right); }, p_pRight);
	case BiaMember::O_ASSIGN_MODULUS:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data % p_right); }, p_pRight);

	case BiaMember::O_BITWISE_OR:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data | p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_AND:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data & p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_XOR:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data ^ p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_ARITHMETIC_LEFT_SHIFT:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data << p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_ARITHMETIC_RIGHT_SHIFT:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data >> p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_LOGICAL_RIGHT_SHIFT:
		return NativeHelperIntegral<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = static_cast<T>(static_cast<std::make_unsigned<T>::type>(p_data) >> p_right);

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_OR:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data | p_right); }, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_AND:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data & p_right); }, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_XOR:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data ^ p_right); }, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data << p_right); }, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(p_data >> p_right); }, p_pRight);
	case BiaMember::O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT:
		return NativeHelperIntegral<int, 0, -1>([&p_data](auto p_right) { p_data = static_cast<T>(static_cast<std::make_unsigned<T>::type>(p_data) >> p_right); }, p_pRight);

	case BiaMember::O_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data == p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_EQUALS_NOT:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data != p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_LESS_THAN:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data < p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_LESS_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data <= p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_GREATER_THAN:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data > p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	case BiaMember::O_GREATER_EQUALS:
		return NativeHelper<int, 1, -1>([&p_data, p_pDestination](auto p_right) {
			auto result = p_data >= p_right;

			(new(p_pDestination) BiaMemberHolder())->Initialize<BiaNativeVariable<utility::BiaUpgrade<decltype(result)>::upgrade>>(result);
		}, p_pRight);
	default:
		break;
	}

	return -1;
}


}
}
}
}