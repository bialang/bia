#pragma once

#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <typeinfo>
#include <type_traits>
#include <utility>

#include "config.hpp"
#include "operator.hpp"
#include "native_type.hpp"
#include "type_traits.hpp"


namespace bia
{
namespace framework
{

class member
{
public:


	enum FLAG : int
	{
		F_NONE = 0,
		F_INT_8 = 0x1,
		F_INT_16 = 0x2,
		F_INT_32 = 0x4,
		F_INT_64 = 0x8,
		F_INT = 0x10,
		F_DOUBLE = 0x20,
		F_STRING = 0x40,
		F_CONST = 0x80
	};

	typedef uint32_t parameter_count;


	/**
	 * Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	*/
	member() noexcept
	{
		_initialized = true;
	}
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~member() noexcept
	{
		_initialized = false;
	}
	/**
	 * Undefines this object.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	*/
	virtual void undefine() noexcept = 0;
	/**
	 * Prints this value to stdout.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	*/
	virtual void print() const = 0;
	/**
	 * Clones this member to the specified location.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @param [out] _destination The specified destination.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If the operation is not supported by the member.
	 * @throws See replace_this().
	*/
	virtual void clone(member * _destination) = 0;
	//virtual void introduce(template_table * _table) = 0;
	/**
	 * Executes this object as function.
	 *
	 * @since 3.64.127.716
	 * @date 28-Apr-18
	 *
	 * @param [in] _instance A corresponding instance. Only needed if this is a member function.
	 * @param [out] _destination The destination of the return result.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If arguments are required or if the instance is null.
	 * @throws See cast().
	*/
	virtual void execute(member * _instance, member * _destination) = 0;
	/**
	 * Executes this object as function with only member parameters.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _instance A corresponding instance. Only needed if this is a member function.
	 * @param [out] _destination The destination of the return result.
	 * @param _count The amount of the passed arguments.
	 * @param ... The arguments.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If the passed arguments are wrong or if the instance is null.
	 * @throws exception::invalid_type If one argument is invalid.
	 * @throws See cast().
	*/
	virtual void execute_count(member * _instance, member * _destination, parameter_count _count...) = 0;
	/**
	 * Executes this object as function with mixed parameters.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [in] _instance A corresponding instance. Only needed if this is a member function.
	 * @param [out] _destination The destination of the return result.
	 * @param _format The types of the arguments.
	 * @param _count The amount of the passed arguments.
	 * @param ... The arguments.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If the passed arguments are wrong or if the instance is null.
	 * @throws exception::invalid_type If one argument is invalid.
	 * @throws See cast().
	*/
	virtual void execute_format(member * _instance, member * _destination, const char * _format, parameter_count _count...) = 0;
	/**
	 * Creates an instance without any parameters.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 *
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	*/
	//virtual void Instantiate(BiaMember * p_pDestination) = 0;
	/**
	 * Creates an instance with only members as parameters.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 * @param	p_unParameterCount	Defines how many parameters are passed.
	 * @param	...	Defines the passed parameters.
	 *
	 * @throws	exception::BadCastException	Thrown when one of the arguments do not match.
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	*/
	//virtual void InstantiateCount(BiaMember * p_pDestination, parameter_count p_unParameterCount, ...) = 0;
	/**
	 * Creates an instance with any type as parameter.
	 *
	 * @param	[in,out]	p_pDestination	Defines the destination of the return result.
	 * @param	p_unParameterCount	Defines how many parameters are passed.
	 * @param	p_pcFormat	Defines the type order of the parameters.
	 * @param	...	Defines the passed parameters.
	 *
	 * @throws	exception::BadCastException	Thrown when one of the arguments do not match.
	 * @throws	exception::BadCallException	Thrown when this member cannot be executed.
	 * @throws	exception::ArgumentException	Thrown when the arguments do not match the function signature.
	*/
	//virtual void InstantiateFormat(BiaMember * p_pDestination, parameter_count p_unParameterCount, const char * p_pcFormat, ...) = 0;
	/**
	 * @throws	exception::OperatorException	Thrown when the operator is not supported.
	 * @throws	exception::BadCallException	Thrown when operations are not supported.
	*/
	
	/**
	 * An operator call with another member as right value.
	 *
	 * @since 3.64.127.716
	 * @date 12-May-18
	 *
	 * @param [out] _destination The operation result.
	 * @param _operator The operator.
	 * @param _right The right member.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::operator_error If the operator is not valid.
	 * @throws exception::access_violation If this member cannot be modified.
	 * @throws exception::execution_error If the operator call is invalid.
	*/
	virtual void operator_call(member * _destination, operator_type _operator, const member * _right) = 0;
	/**
	 * An operator call with an int32 as right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [out] _destination The operation result.
	 * @param _operator The operator.
	 * @param _right The right value.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::operator_error If the operator is not valid.
	 * @throws exception::access_violation If this member cannot be modified.
	 * @throws exception::execution_error If the operator call is invalid.
	*/
	virtual void operator_call_int32(member * _destination, operator_type _operator, int32_t _right) = 0;
	/**
	 * An operator call with an int64 as right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [out] _destination The operation result.
	 * @param _operator The operator.
	 * @param _right The right value.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::operator_error If the operator is not valid.
	 * @throws exception::access_violation If this member cannot be modified.
	 * @throws exception::execution_error If the operator call is invalid.
	*/
	virtual void operator_call_int64(member * _destination, operator_type _operator, int64_t _right) = 0;
	/**
	 * An operator call with a double as right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [out] _destination The operation result.
	 * @param _operator The operator.
	 * @param _right The right value.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::operator_error If the operator is not valid.
	 * @throws exception::access_violation If this member cannot be modified.
	 * @throws exception::execution_error If the operator call is invalid.
	*/
	virtual void operator_call_double(member * _destination, operator_type _operator, double _right) = 0;
	//virtual void operator_call_string(member * _destination, operator_type _operator, const char * _right) = 0;
	/**
	 * @throws	exception::OperatorException
	*/
	/*virtual void OperatorAssignCall(uint32_t p_unOperator, BiaMember * p_pRight) = 0;
	virtual void OperatorAssignCallInt_32(uint32_t p_unOperator, int32_t p_nRight) = 0;
	virtual void OperatorAssignCallInt_64(uint32_t p_unOperator, int64_t p_llRight) = 0;
	virtual void OperatorAssignCallFloat(uint32_t p_unOperator, float p_rRight) = 0;
	virtual void OperatorAssignCallDouble(uint32_t p_unOperator, double p_rRight) = 0;
	virtual void OperatorAssignCallString(uint32_t p_unOperator, const char * p_szRight) = 0;*/
	/**
	 * @throws	exception::OperatorException
	*/
	//virtual void OperatorSelfCall(uint32_t p_unOperator) = 0;
	/**
	 * Checks whether the specified type matches this object.
	 *
	 * @param	p_type	Defines the type.
	 *
	 * @return	true if they match, otherwise false.
	*/
	//virtual bool is_custom_type(const std::type_info & _type) const = 0;
	/**
	 * Some details about the content.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 *
	 * @return See @ref member::FLAG.
	*/
	virtual int get_flags() const = 0;
	/**
	 * Tests the contents of this member.
	 *
	 * @since 3.64.127.716
	 * @date 5-May-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If a test call is invalid.
	 *
	 * @return A non-zero value for the boolean value true, otherwise 0 for false.
	*/
	virtual int32_t test() const = 0;
	/**
	 * Tests the contents of this member to the right member.
	 *
	 * @since 3.64.131.727
	 * @date 14-Jun-18
	 *
	 * @param _operator The operator.
	 * @param _right The right member.

	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If a test call is invalid.
	 * @throws exception::operator_error If the operator is invalid.
	 *
	 * @return A non-zero value for the boolean value true, otherwise 0 for false.
	*/
	virtual int32_t test_member(operator_type _operator, member * _right) const = 0;
	/**
	 * Tests the contents of this member to the right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _operator The operator.
	 * @param _right The right value.

	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If a test call is invalid.
	 * @throws exception::operator_error If the operator is invalid.
	 *
	 * @return A non-zero value for the boolean value true, otherwise 0 for false.
	*/
	virtual int32_t test_int32(operator_type _operator, int32_t _right) const = 0;
	/**
	 * Tests the contents of this member to the right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _operator The operator.
	 * @param _right The right value.

	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If a test call is invalid.
	 * @throws exception::operator_error If the operator is invalid.
	 *
	 * @return A non-zero value for the boolean value true, otherwise 0 for false.
	*/
	virtual int32_t test_int64(operator_type _operator, int64_t _right) const = 0;
	/**
	 * Tests the contents of this member to the right value.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param _operator The operator.
	 * @param _right The right value.

	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If a test call is invalid.
	 * @throws exception::operator_error If the operator is invalid.
	 *
	 * @return A non-zero value for the boolean value true, otherwise 0 for false.
	*/
	virtual int32_t test_double(operator_type _operator, double _right) const = 0;
	/**
	 * Returns the int representation of the content.
	 *
	 * @since 3.64.132.729
	 * @date 15-Jun-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If no representation is available.
	 *
	 * @return The int representation.
	*/
	virtual int64_t to_int() const = 0;
	/**
	 * Returns the double representation of the content.
	 *
	 * @since 3.64.132.729
	 * @date 15-Jun-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If no representation is available.
	 *
	 * @return The double representation.
	*/
	virtual double to_double() const = 0;
	/**
	 * Compares this object to the right hand value.
	 *
	 * @throws	exception::BadCallException	Thrown when the member cannot be tested.
	 * @throws	exception::OperatorException	Thrown when the operation is not valid.
	 *
	 * @return	A non-zero value for a successful result, otherwise 0.
	*/
	//virtual int32_t TestCallString(uint32_t p_unOperator, const char * p_szRight) = 0;
	/**
	 * Returns the member address matching the given name.
	 *
	 * @param	p_szName	Defines the zero-terminated name.
	 *
	 * @throws	exception::SymbolException	Thrown when the member is not known.
	 *
	 * @return	The address of the member.
	*/
	//virtual BiaMember * GetMember(const char * p_szName) = 0;
	/**
	 * Casts this member to the specified mutable type.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam _Ty The required type. References will be converted to pointers.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::invalid_type If this member cannot be casted to _Ty.
	 *
	 * @return A point containing the casted type.
	*/
	template<typename _Ty, typename _T = typename std::remove_reference<_Ty>::type>
	typename std::enable_if<utility::negation<std::is_const<_T>::value>::value, _T*>::type cast()
	{
		// Native type
		if (native::determine_native_type<_T>() != native::NATIVE_TYPE::CUSTOM) {
			return static_cast<_T*>(get_native_data(native::determine_native_type<_T>()));
		} // Custom type
		else {
			return static_cast<_T*>(get_data(typeid(_T)));
		}
	}
	/**
	 * Casts this member to the specified immutable type.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam _Ty The required type. References will be converted to pointers.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::invalid_type If this member cannot be casted to _Ty.
	 *
	 * @return A point containing the casted type.
	*/
	template<typename _Ty, typename _T = typename std::remove_reference<_Ty>::type>
	typename std::enable_if<std::is_const<_T>::value, _T*>::type cast() const
	{
		// Native type
		if (native::determine_native_type<_T>() != native::NATIVE_TYPE::CUSTOM) {
			return static_cast<_T*>(get_const_native_data(native::determine_native_type<_T>()));
		} // Custom type
		else {
			return static_cast<_T*>(get_const_data(typeid(_T)));
		}
	}
	/**
	 * Replaces this obejct with the new defined one.
	 *
	 * @remarks No size checking is performed. Be very cautious! Use this function only if you know that this object has enough space.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	 *
	 * @tparam _Ty The new member type. Must be a deriviate of \ref member.
	 * @tparam _Args The arguments that should be passed to the constructor.
	 *
	 * @param _args Defines the arguments used to create the new object.
	 *
	 * @throws ... See the destructor of this class and the constructor of the new class.
	 *
	 * @return The newly constructed object.
	*/
	template<typename _Ty, typename... _Args>
	typename std::enable_if<std::is_base_of<member, _Ty>::value, _Ty*>::type replace_this(_Args &&... _args)
	{
		// Destroy this
		this->~member();

		// Construct new object
		return new(this) _Ty(std::forward<_Args>(_args)...);
	}

protected:
	/** If true this object was initialized, otherwise not. */
	bool _initialized;

	/**
	 * Returns a pointer to mutable native data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.s
	 * @throws exception::invalid_type If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual void * get_native_data(native::NATIVE_TYPE _type) = 0;
	/**
	 * Returns a pointer to immutable native data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::invalid_type If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual const void * get_const_native_data(native::NATIVE_TYPE _type) const = 0;
	/**
	 * Returns a pointer to mutable custom data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::invalid_type If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual void * get_data(const std::type_info & _type) = 0;
	/**
	 * Returns a pointer to immutable custom data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::invalid_type If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual const void * get_const_data(const std::type_info & _type) const = 0;
};

}
}