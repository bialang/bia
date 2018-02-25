#pragma once

#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <typeinfo>
#include <type_traits>
#include <utility>


namespace bia
{
namespace framework
{

class BiaMember
{
public:
	enum OPERATOR : uint32_t
	{
		O_ASSIGN = 0x3d,

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
		NTF_NONE = 0,
		NTF_INT_8 = 0x1,
		NTF_INT_16 = 0x2,
		NTF_INT_32 = 0x4,
		NTF_INT_64 = 0x8,
		NTF_FLOAT = 0x10,
		NTF_DOUBLE = 0x20,
		NTF_STRING = 0x40
	};

	typedef uint32_t parameter_count;


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
	 * Undefines this object.
	*/
	virtual void Undefine() = 0;
	/**
	 * Prints the contents of this object.
	*/
	virtual void Print() = 0;
	/**
	 * Calls this function without any parameters.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 *
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	 * @throws	exception::InstanceException	Thrown when the passed instance is invalid.
	*/
	virtual void Call(BiaMember * p_pInstance, BiaMember * p_pDestination) = 0;
	/**
	 * Calls this function with only members as parameters.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 * @param	p_unParameterCount	Defines how many parameters are passed.
	 * @param	...	Defines the passed parameters.
	 *
	 * @throws	exception::BadCastException	Thrown when one of the arguments do not match.
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	 * @throws	exception::InstanceException	Thrown when the passed instance is invalid.
	*/
	virtual void CallCount(BiaMember * p_pInstance, BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) = 0;
	/**
	 * Calls this function with any type as parameter.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 * @param	p_szFormat	Defines the type order of the parameters.
	 * @param	...	Defines the passed parameters.
	 *
	 * @throws	exception::BadCastException	Thrown when one of the arguments do not match.
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	 * @throws	exception::InstanceException	Thrown when the passed instance is invalid.
	*/
	virtual void CallFormat(BiaMember * p_pInstance, BiaMember * p_pDestination, const char * p_szFormat, ...) = 0;
	/**
	 * @throws	exception::OperatorException	Thrown when the operation is not supported.
	*/
	virtual void OperatorCall(uint32_t p_unOperator, BiaMember * p_pRight, BiaMember * p_pDestination) = 0;
	virtual void OperatorCallInt_32(uint32_t p_unOperator, int32_t p_nRight, BiaMember * p_pDestination) = 0;
	virtual void OperatorCallInt_64(uint32_t p_unOperator, int64_t p_llRight, BiaMember * p_pDestination) = 0;
	virtual void OperatorCallFloat(uint32_t p_unOperator, float p_rRight, BiaMember * p_pDestination) = 0;
	virtual void OperatorCallDouble(uint32_t p_unOperator, double p_rRight, BiaMember * p_pDestination) = 0;
	/**
	 * @throws	exception::OperatorException
	*/
	virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) = 0;
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) = 0;
	virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) = 0;
	virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) = 0;
	virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) = 0;
	/**
	 * @throws	exception::OperatorException
	*/
	virtual void OperatorSelfCall(uint32_t p_unOperator) = 0;
	/**
	 * Clones the contents of this object to the destination.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination.
	*/
	virtual void Clone(BiaMember * p_pDestination) = 0;
	/**
	 * Checks whether the specified type matches this object.
	 *
	 * @param	p_type	Defines the type.
	 *
	 * @return	true if they match, otherwise false.
	*/
	virtual bool IsType(const std::type_info & p_type) const = 0;
	virtual int GetNativeType() const = 0;
	/**
	 * Tests the content of this object.
	 *
	 * @throws	exception::BadCallException	Thrown when the member cannot be tested.
	 *
	 * @return	A non-zero value for a successful result, otherwise 0.
	*/
	virtual int32_t Test() = 0;
	/**
	 * Returns the member address matching the given name.
	 *
	 * @param	p_szName	Defines the zero-terminated name.
	 *
	 * @throws	exception::SymbolException	Thrown when the member is not known.
	 *
	 * @return	The address of the member.
	*/
	virtual BiaMember * GetMember(const char * p_szName) = 0;
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
	template<typename T, typename... _ARGS>
	inline typename std::enable_if<std::is_base_of<BiaMember, T>::value, T*>::type ReplaceObject(_ARGS &&... p_args)
	{
		//Destroy this
		this->~BiaMember();

		//Construct new object
		return new(this) T(std::forward<_ARGS>(p_args)...);
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
		CONST_STRING,
		CUSTOM
	};

	/**	If true this object was initialized, otherwise not.	*/
	bool m_bInitialized;

	/**
	 * Returns the data depending on the native type.
	 *
	 * @param	p_nativeType	Defines the type.
	 *
	 * @throws	exception::BadCastException	Thrown when the type is not supported.
	 *
	 * @return	The address to the data.
	*/
	virtual void * GetNativeData(NATIVE_TYPE p_nativeType) = 0;
	/**
	 * Returns the data depending on the type.
	 *
	 * @param	p_type	Defines the type.
	 * @param	p_bConst	Defines how the data will be accessed.
	 *
	 * @throws	exception::BadCastException	Thrown when the type is not supported.
	 *
	 * @return	The address to the data.
	*/
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
		else if (std::is_same<T, const char*>::value)
			return NATIVE_TYPE::CONST_STRING;

		return NATIVE_TYPE::CUSTOM;
	}
};

}
}