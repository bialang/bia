#pragma once

#include "../stack.hpp"

#include <cstdint>
#include <external/big_int.hpp>
#include <gc/object.hpp>

namespace bia {
namespace bvm {
namespace framework {

class member : public bia::gc::object
{
public:
	typedef unsigned int parameter_count_type;
	typedef int operator_type;
	typedef int flag_type;
	typedef int bool_type;

	virtual ~member() = default;

	/*
	 Binds the given member to this object. This object refers to the member as its parent.

	 @param[in] parent is the parent (scope)
	*/
	virtual void bind(member* parent) = 0;
	/*
	 Returns the set flags of this member.

	 @returns the flags
	*/
	virtual flag_type flags() const										 = 0;
	virtual bool_type test() const										 = 0;
	virtual bool_type test_member(operator_type op, member* other) const = 0;
	/*
	 Creates a shallow copy of this object. Every child object will be cloned.

	 @returns a shallow copy
	*/
	virtual member* shallow_copy() = 0;
	/*
	 Creates a deep copy of this object. Every child object will be deep copied unlike in shallow_copy().

	 @returns a deep copy
	*/
	virtual member* deep_copy() = 0;
	/*
	 Copies or creates a reference to this object based on its type and default behavior.

	 @return a copy or reference
	*/
	virtual member* clone() = 0;
	/*
	 Returns a reference to the object with the corresponding name.

	 @returns the reference
	*/
	virtual member* get_member(const char16_t* name) = 0;
	/*
	 Executes this member without any parameters.

	 @param[in] s is the used bvm stack
	*/
	virtual member* execute(stack* s)									= 0;
	virtual member* execute_count(stack* s, parameter_count_type count) = 0;
	virtual member* execute_format(stack* s, parameter_count_type count,
								   const char* format)					= 0;
	virtual member* operator_call(operator_type op, member* other)		= 0;
	/*
	 Converts this object to an integer representation.

	 @returns this object as an integer
	*/
	virtual bia::external::big_int to_int() const = 0;
	/*
	 Converts this object to an floating point representation.

	 @returns this object as an floating point
	*/
	virtual double to_double() const = 0;

protected:
};

} // namespace framework
} // namespace bvm
} // namespace bia