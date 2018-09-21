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
#include "string_manager.hpp"


namespace bia
{
namespace framework
{

/**
 * @brief The base of all members.
 *
 * The base class of all variables Bia knows.
*/
class member
{
public:
	enum FLAG : int
	{
		/** No flags specified. */
		F_NONE = 0,
		/** The member is an integer. */
		F_INT = 0x1,
		/** The member is a double. */
		F_DOUBLE = 0x2,
		/** The member is a string. */
		F_STRING = 0x4,
		/** The member cannot be modified. */
		F_CONST = 0x8,
		/** The member can be displayed as an integer. */
		F_TO_INT = 0x10,
		/** The member can be displayed as a double. */
		F_TO_DOUBLE = 0x20
	};

	/** The type of the parameter count. */
	typedef uint32_t parameter_count;


	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	*/
	virtual ~member() noexcept = default;
	/**
	 * Undefines this object.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	 *
	 * @throws See replace_this().
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION undefine() = 0;
	/**
	 * Prints this value to stdout.
	 *
	 * @since 3.64.127.716
	 * @date 8-Apr-18
	 *
	 * @throws exception::symbol_error If this member is not valid.
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION print() const = 0;
	/**
	 * Copy this member to the specified destination.
	 *
	 * @since 3.65.132.736
	 * @date 30-Jul-18
	 *
	 * @param [in,out] _destination The destionation member.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If the operation is not supported by the member.
	 * @throws See replace_this().
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION copy(member * _destination) = 0;
	/**
	 * Creates a reference to this member.
	 *
	 * @since 3.65.132.736
	 * @date 30-Jul-18
	 *
	 * @param [in,out] _destination The destionation member.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If the operation is not supported by the member.
	 * @throws See replace_this().
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION refer(member * _destination) = 0;
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
	virtual void BIA_MEMBER_CALLING_CONVENTION clone(member * _destination) = 0;
	/**
	 * Executes this object as function.
	 *
	 * @since 3.64.127.716
	 * @date 28-Apr-18
	 *
	 * @param [out] _destination The destination of the return result.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If arguments are required.
	 * @throws See cast().
	 * @throws See force::initiator::instantiate().
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION execute(member * _destination) = 0;
	/**
	 * Executes this object as function with only member parameters.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [out] _destination The destination of the return result.
	 * @param _reserved Reserved parameter. Do not use this.
	 * @param _count The amount of the passed arguments.
	 * @param ... The arguments.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If the passed arguments are wrong.
	 * @throws exception::type_error If one argument is invalid.
	 * @throws See cast().
	 * @throws See force::initiator::instantiate_count().
	*/
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_count(member * _destination, void * _reserved, parameter_count _count...) = 0;
	/**
	 * Executes this object as function with mixed parameters.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	 *
	 * @param [out] _destination The destination of the return result.
	 * @param _format The types of the arguments.
	 * @param _count The amount of the passed arguments.
	 * @param ... The arguments.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::execution_error If this object cannot be executed.
	 * @throws exception::argument_error If the passed arguments are wrong.
	 * @throws exception::type_error If one argument is invalid.
	 * @throws See cast().
	 * @throws See force::initiator::instantiate_format().
	*/
	virtual void BIA_VARG_MEMBER_CALLING_CONVENTION execute_format(member * _destination, const char * _format, parameter_count _count...) = 0;
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
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call(member * _destination, operator_type _operator, const member * _right) = 0;
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
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int32(member * _destination, operator_type _operator, int32_t _right) = 0;
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
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_int64(member * _destination, operator_type _operator, int64_t _right) = 0;
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
	virtual void BIA_MEMBER_CALLING_CONVENTION operator_call_double(member * _destination, operator_type _operator, double _right) = 0;
	/**
	 * Returns a member of this member.
	 *
	 * @remarks This and @a _destination can be the same address.
	 *
	 * @since 3.66.135.747
	 * @date 5-Aug-18
	 *
	 * @param [out] _destination The member.
	 * @param _name The name of the member.
	 *
	 * @throws exception::symbol_error If this member or the wanted member is not valid.
	*/
	virtual void BIA_MEMBER_CALLING_CONVENTION object_member(member * _destination, machine::string_manager::name_type _name) = 0;
	/**
	 * Sets the instance of the member.
	 *
	 * @since 3.67.135.755
	 * @date 8-Aug-18
	 *
	 * @param _instance The instance holder.
	 * @param _type The type of the instance.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If the instance type is not the right one.
	*/
	virtual void set_instance(const void * _instance, const std::type_info & _type) = 0;
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
	virtual int flags() const = 0;
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
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test() const = 0;
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
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_member(operator_type _operator, member * _right) const = 0;
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
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int32(operator_type _operator, int32_t _right) const = 0;
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
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_int64(operator_type _operator, int64_t _right) const = 0;
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
	virtual int32_t BIA_MEMBER_CALLING_CONVENTION test_double(operator_type _operator, double _right) const = 0;
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
	 * Casts this member to the specified mutable type.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @tparam _Ty The required type. References will be converted to pointers.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If this member cannot be casted to _Ty.
	 *
	 * @return A point containing the casted type.
	*/
	template<typename _Ty, typename _T = typename std::remove_reference<_Ty>::type>
	typename std::enable_if<utility::negation<std::is_const<typename std::remove_pointer<_T>::type>::value>::value, _T*>::type cast()
	{
		// Native type
		if (native::determine_native_type<_T>() != native::NATIVE_TYPE::CUSTOM) {
			return static_cast<_T*>(native_data(native::determine_native_type<_T>()));
		} // Custom type
		else {
			return static_cast<_T*>(data(typeid(_T)));
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
	 * @throws exception::type_error If this member cannot be casted to _Ty.
	 *
	 * @return A point containing the casted type.
	*/
	template<typename _Ty, typename _T = typename std::remove_reference<_Ty>::type>
	typename std::enable_if<std::is_const<typename std::remove_pointer<_T>::type>::value, _T const*>::type cast() const
	{
		// Native type
		if (native::determine_native_type<_T>() != native::NATIVE_TYPE::CUSTOM) {
			return static_cast<_T const*>(const_native_data(native::determine_native_type<_T>()));
		} // Custom type
		else {
			return static_cast<_T const*>(const_data(typeid(_T)));
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
	/**
	 * Returns a pointer to mutable native data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual void * native_data(native::NATIVE_TYPE _type) = 0;
	/**
	 * Returns a pointer to immutable native data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual const void * const_native_data(native::NATIVE_TYPE _type) const = 0;
	/**
	 * Returns a pointer to mutable custom data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual void * data(const std::type_info & _type) = 0;
	/**
	 * Returns a pointer to immutable custom data.
	 *
	 * @since 3.64.127.716
	 * @date 21-Apr-18
	 *
	 * @param _type The type.
	 *
	 * @throws exception::symbol_error If this member is not valid.
	 * @throws exception::type_error If the type is not supported.
	 *
	 * @return A pointer to the data.
	*/
	virtual const void * const_data(const std::type_info & _type) const = 0;
};

}
}
