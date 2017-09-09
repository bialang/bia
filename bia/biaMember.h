#pragma once

#include <typeinfo>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <memory>

#include "biaGlobal.h"
#include "biaType.h"
#include "biaKey.h"
#include "biaHasher.h"

#define BIA_TYPE_COMPARE(x, y) (x == y)


namespace bia
{
namespace api
{
namespace framework
{

typedef std::unordered_map<machine::BiaKey, machine::scope::BiaScopeElement, utility::bia_hasher> members;
typedef std::map<uint32_t, std::unique_ptr<object::BiaClassOperatorBase>> operators;


class BiaMember
{
public:
	enum FLAGS : unsigned int
	{
		F_FUNCTION = 0x1,
		F_VARIABLE = 0x2,
		F_CONST = 0x4,
		F_STATIC = 0x8,	/**	If set, defines a static member, otherwise a non-static.	*/

		F_NATIVE_LONG = 0x10,
		F_NATIVE_INT = 0x20,
		F_NATIVE_SHORT = 0x30,
		F_NATIVE_BYTE = 0x40,
		F_NATIVE_DOUBLE = 0x50,
		F_NATIVE_FLOAT = 0x60,
		F_NATIVE_STRING = 0x70,
		F_NATIVE_TYPE_MASK = 0x70,

		F_CLASS = 0x100,
	};
	enum OPERATORS : uint32_t
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
	enum class SET_PARAMETER
	{
		CLASS_PROMOTE_PARAMS
	};
	enum class GET_PARAMETER
	{
		CLASS_HASH_CODE
	};
	struct CLASS_PROMOTE_PRAMAS
	{
		const std::shared_ptr<members> * pMembers;
		const std::shared_ptr<operators> * pOperators;
	};
	union SET_PARAMETER_DATA
	{
		CLASS_PROMOTE_PRAMAS classPromoteParams;
	};
	union GET_PARAMETER_DATA
	{
		size_t iClassHashCode;
	};


	inline virtual ~BiaMember() = default;
	/**
	 * Prints the contents of the member to the console.
	*/
	virtual void Print() const = 0;
	/**
	 * Sets a parameter.
	 *
	 * @param	p_type	Defines the type of the parameter.
	 * @param	p_data	Defines the data.
	*/
	virtual void SetParameter(SET_PARAMETER p_type, SET_PARAMETER_DATA p_data) = 0;
	/**
	 * Retrieves a parameter.
	 *
	 * @param	p_type	Defines the type of the parameter.
	 * @param	[out]	p_data	Defines the data.
	 *
	 * @return True if the returned data is valid, otherwise false.
	*/
	virtual bool GetParameter(GET_PARAMETER p_type, GET_PARAMETER_DATA & p_data) = 0;
	/**
	 * Makes a clone of this member at the specified destination.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination for the clone.
	 *
	 * @return	true if it succeeded, otherwise false.
	*/
	virtual bool Clone(void * p_pDestination) = 0;
	/**
	 * Stores the specified value in this member.
	 *
	 * @param	[in]	p_pRight	Defines the value that should be stored.
	 *
	 * @return	true if it succeeded, otherwise false.
	*/
	virtual bool Store(BiaMember * p_pRight) = 0;
	/**
	 * Increments this member if possible.
	 *
	 * @return	true if it succeeded, otherwise false.
	*/
	virtual bool Inc() = 0;
	/**
	 * Decrements this member if possible.
	 *
	 * @return	true if it succeeded, otherwise false.
	*/
	virtual bool Dec() = 0;
	/**
	 * Casts this member to the specified type.
	 *
	 * @param   [out]	p_pOutput	Defines the output.
	 *
	 * @return  true if the output is valid, otherwise false.
	*/
	template<typename T>
	inline bool Cast(T *& p_pOutput)
	{
		using _TYPE = typename std::remove_cv<T>::type;

		//String
		if (std::is_same<_TYPE, std::string>::value && IsType(NATIVE_TYPE::STRING, false))
		{
			p_pOutput = static_cast<_TYPE*>(LoadNative());

			return true;
		}
		//String reference
		else if (((std::is_same<T, std::string*>::value || std::is_same<T, const std::string*>::value) && IsType(NATIVE_TYPE::STRING, false)) ||
			(std::is_same<T, const char*>::value && IsType(NATIVE_TYPE::STRING, true)))
		{
			p_pOutput = static_cast<_TYPE*>(LoadPtr(std::is_same<T, const char*>::value ? PTR_TYPE::CONST_CHAR : PTR_TYPE::NORMAL));

			return true;
		}
		//Native
		else if ((std::is_same<_TYPE, double>::value && IsType(NATIVE_TYPE::DOUBLE, false)) ||
			(std::is_same<_TYPE, float>::value && IsType(NATIVE_TYPE::FLOAT, false)) ||
			(std::is_integral<_TYPE>::value && IsType(NATIVE_TYPE::LONG, false)))
		{
			p_pOutput = static_cast<_TYPE*>(LoadNative());

			return true;
		}
		//Native reference TODO: removee  const char*
		else if ((std::is_same<T, double*>::value && IsType(NATIVE_TYPE::DOUBLE, false)) ||
			(std::is_same<T, float*>::value && IsType(NATIVE_TYPE::FLOAT, false)) ||
			(std::is_integral<std::remove_pointer<T>::type>::value && !std::is_const<std::remove_pointer<T>::type>::value && IsType(DetermineNativeIntegral<std::remove_pointer<T>::type>(), false)) ||
			(std::is_same<T, const double*>::value && IsType(NATIVE_TYPE::DOUBLE, true)) ||
			(std::is_same<T, const float*>::value && IsType(NATIVE_TYPE::FLOAT, true)) ||
			(std::is_integral<std::remove_pointer<T>::type>::value && std::is_const<std::remove_pointer<T>::type>::value && IsType(DetermineNativeIntegral<std::remove_pointer<T>::type>(), true)))
		{
			p_pOutput = static_cast<_TYPE*>(LoadPtr(PTR_TYPE::NORMAL));

			return true;
		}
		else
		{
			switch (IsType(typeid(utility::BiaPointerRank<_TYPE>::_TYPE), utility::BiaPointerRank<_TYPE>::VALUE, std::is_const<utility::BiaPointerRank<T>::_TYPE>::value))
			{
			case TYPE::NATIVE:
			{
				p_pOutput = static_cast<_TYPE*>(LoadNative());

				return true;
			}
			case TYPE::POINTER:
			{
				p_pOutput = static_cast<_TYPE*>(LoadPtr(PTR_TYPE::NORMAL));

				return true;
			}
			case TYPE::INVALID:
			default:
				return false;
			}
		}
	}
	virtual bool LoadObject(const machine::BiaKey & p_object, void * p_pScopeReferenceDestination) = 0;
	/**
	 * Returns the conditional output of this member.
	 *
	 * @return	Conditional: 1 = true, 0 = false; If -1 is returned, the call was invalid.
	*/
	virtual int Conditional() const = 0;
	virtual int Operator(unsigned int p_uiOperator, void * p_pDestination, BiaMember * p_pRight) = 0;
	virtual int SelfOperator(unsigned int p_uiOperator, void * p_pDestination) = 0;
	/**
	* Executes this member as function.
	*
	* @param	[out]	p_pDestination	Defines the output of the return value. Only valid if 1 was returned.
	* @param	[in,out]	p_pBegin	Defines the beginning of the parameter list.
	* @param	p_pEnd	Defines the end of the parameter list.
	*
	* @return	Returns -1 if it fails; 0 on success (void); 1 on success and a return value written to the destination.
	*/
	virtual int Execute(void * p_pReturnDestination, void * p_pInstance, BiaParameter * p_pBegin, const BiaParameter * p_pEnd, machine::BiaMachineContext * p_pContext) = 0;
	virtual int Call(const machine::BiaKey & p_function, void * p_pReturnDestination, BiaParameter * p_pBegin, const BiaParameter * p_pEnd) = 0;
	virtual unsigned int GetFlags() const = 0;

protected:
	enum class PTR_TYPE
	{
		NORMAL,
		CONST_CHAR
	};
	enum class TYPE
	{
		INVALID,
		NATIVE,
		POINTER,
	};
	enum class NATIVE_TYPE
	{
		LONG,
		INT,
		SHORT,
		BYTE,
		DOUBLE,
		FLOAT,
		STRING
	};

	virtual void * LoadNative() = 0;
	virtual void * LoadPtr(PTR_TYPE p_type) = 0;
	virtual TYPE IsType(const std::type_info & p_type, unsigned int p_unPointerRank, bool p_bConst) const = 0;
	virtual bool IsType(NATIVE_TYPE p_type, bool p_bConst) const = 0;

private:
	template<typename T>
	inline static NATIVE_TYPE DetermineNativeIntegral()
	{
		if (std::is_same<T, long long>::value || std::is_same<T, unsigned long long>::value)
			return NATIVE_TYPE::LONG;
		else if (std::is_same<T, long>::value || std::is_same<T, unsigned long>::value ||
			std::is_same<T, int>::value || std::is_same<T, unsigned int>::value)
			return NATIVE_TYPE::INT;
		else if (std::is_same<T, short>::value || std::is_same<T, unsigned short>::value)
			return NATIVE_TYPE::SHORT;
		else
			return NATIVE_TYPE::BYTE;
	}
};

}
}
}