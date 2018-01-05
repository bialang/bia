#pragma once

#include <cstdio>
#include <cstdint>
#include <typeinfo>
#include <type_traits>


namespace bia
{
namespace framework
{

class BiaMember
{
public:
	enum OPERATOR : uint32_t
	{
		O_PLUS = 0x2b,
		O_MINUS = 0x2d,
		O_DIVIDE = 0x2f,
		O_MODULUS = 0x25,
		O_MULTIPLY = 0x2a,
		O_ASSIGN_PLUS = 0x3d2b,
		O_ASSIGN_MINUS = 0x3d2d,
		O_ASSIGN_DIVIDE = 0x3d2f,
		O_ASSIGN_MODULUS = 0x3d25,
		O_ASSIGN_MULTIPLY = 0x3d2a,

		O_BITWISE_OR = 0x7c,
		O_BITWISE_AND = 0x26,
		O_BITWISE_XOR = 0x5e,
		O_BITWISE_INVERT = 0x7e,
		O_BITWISE_ARITHMETIC_LEFT_SHIFT = 0x3c3c,
		O_BITWISE_ARITHMETIC_RIGHT_SHIFT = 0x3e3e,
		O_BITWISE_LOGICAL_RIGHT_SHIFT = 0x3e3e3e,
		O_BITWISE_ASSIGN_OR = 0x3d7c,
		O_BITWISE_ASSIGN_AND = 0x3d26,
		O_BITWISE_ASSIGN_XOR = 0x3d5e,
		O_BITWISE_ASSIGN_ARITHMETIC_LEFT_SHIFT = 0x3d3c3c,
		O_BITWISE_ASSIGN_ARITHMETIC_RIGHT_SHIFT = 0x3d3e3e,
		O_BITWISE_ASSIGN_LOGICAL_RIGHT_SHIFT = 0x3d3e3e3e,

		O_EQUALS = 0x3d3d,
		O_EQUALS_NOT = 0x3d21,
		O_LESS_THAN = 0x3c,
		O_LESS_EQUALS = 0x3d3c,
		O_GREATER_THAN = 0x3e,
		O_GREATER_EQUALS = 0x3d3e,
	};
	
	enum NATIVE_TYPE_FLAG : int
	{
		NTF_INT_8 = 0x1,
		NTF_INT_16 = 0x2,
		NTF_INT_32 = 0x4,
		NTF_INT_64 = 0x8,
		NTF_FLOAT = 0x10,
		NTF_DOUBLE = 0x20,
	};

	/**
	 * Constructor.
	*/
	inline BiaMember()
	{
		m_bInitialized = true;
	}
	inline virtual ~BiaMember()
	{
		m_bInitialized = false;
	}


	/**
	 * Prints the contents of this object.
	 *
	 * @since	3.42.93.567
	 * @date	18-Dec-17
	*/
	inline virtual void Print()
	{
		printf("<Empty member at %p>", this);
	}
	/**
	 * @throws	exception::OperatorException
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, void * p_pDestination) = 0;
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, void * p_pDestination) = 0;
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_nRight, void * p_pDestination) = 0;
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, void * p_pDestination) = 0;
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, void * p_pDestination) = 0;
	/**
	 * @throws	exception::OperatorException
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) = 0;
	/**
	 * @throws	exception::OperatorException
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) = 0;
	virtual void Clone(void * p_pDestination) = 0;
	/**
	 * Checks whether the specified type matches this object.
	 *
	 * @param	p_type	Defines the type.
	 *
	 * @return	true if they match, otherwise false.
	*/
	virtual bool IsType(const std::type_info & p_type) const = 0;
	virtual int GetNativeType() const = 0;
	template<typename T, typename _T = typename std::remove_reference<T>::type>
	inline _T * Cast()
	{
		//Native type
		if (NativeType<_T>() != NATIVE_TYPE::CUSTOM)
			return static_cast<_T*>(GetNativeData(NativeType<_T>()));
		//Custom type
		else
			return static_cast<_T*>(GetData(typeid(_T), std::is_const<_T>::value));
	}

protected:
	enum class NATIVE_TYPE
	{
		INT_8,
		CONST_INT_8,
		INT_16,
		CONST_INT_16,
		INT_32,
		CONST_INT_32,
		INT_64,
		CONST_INT_64,
		FLOAT,
		CONST_FLOAT,
		DOUBLE,
		CONST_DOUBLE,
		CUSTOM
	};

	bool m_bInitialized;

	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) = 0;
	virtual void * GetData(const std::type_info & p_type, bool p_bConst) = 0;
private:
	template<typename T>
	inline constexpr static NATIVE_TYPE NativeType()
	{
		if (std::is_integral<T>::value)
		{
			switch (sizeof(T))
			{
			case 1:
				return std::is_const<T>::value ? NATIVE_TYPE::CONST_INT_8 : NATIVE_TYPE::INT_8;
			case 2:
				return std::is_const<T>::value ? NATIVE_TYPE::CONST_INT_16 : NATIVE_TYPE::INT_16;
			case 4:
				return std::is_const<T>::value ? NATIVE_TYPE::CONST_INT_32 : NATIVE_TYPE::INT_32;
			case 8:
				return std::is_const<T>::value ? NATIVE_TYPE::CONST_INT_64 : NATIVE_TYPE::INT_64;
			}
		}
		else if (std::is_same<T, float>::value)
			return std::is_const<T>::value ? NATIVE_TYPE::CONST_FLOAT : NATIVE_TYPE::FLOAT;
		else if (std::is_same<T, double>::value)
			return std::is_const<T>::value ? NATIVE_TYPE::CONST_DOUBLE : NATIVE_TYPE::DOUBLE;

		return NATIVE_TYPE::CUSTOM;
	}
};

}
}