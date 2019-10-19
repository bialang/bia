#pragma once

#include <cstdint>
#include <gc/gc.hpp>
#include <typeinfo>
#include <stack/stack.hpp>

namespace bia {
namespace member {

/*
 The parent type for all member types. All members are gc objects and must provide the following functions.
*/
class member : public gc::object
{
public:
	typedef unsigned int param_count_type;
	typedef int operator_type;
	/* the flag type */
	typedef int flag_type;
	/* the type for testing operations */
	typedef int bool_type;

	/*
	 Additional flags describing the member and how its going to behave in certain situations.
	*/
	enum FLAG : flag_type
	{
		F_NONE = 0,
		/* describes that this member can be mutated */
		F_MUTABLE = 0x1,
	};

	virtual ~member() = default;

	/*
	 Returns the set flags of this member.

	 @returns the flags
	*/
	virtual flag_type flags() const = 0;
	/*
	 Creates a shallow copy of this object. Every child object will be cloned.

	 @returns a shallow copy
	*/
	virtual member* shallow_copy() const = 0;
	/*
	 Creates a deep copy of this object. Every child object will be deep copied unlike in shallow_copy().

	 @returns a deep copy
	*/
	virtual member* deep_copy() const = 0;
	/*
	 Calls this member with `param_count` parameters from the stack.

	 @param[in] stack is the machine stack
	 @param param_count the amount of parameters to pass
	 @returns the return value of the function call
	*/
	virtual member* call(stack::stack* stack, std::int32_t param_count) = 0;
	/*
	 Tests this member.

	 @returns a `1` if the test succeeded, otherwise `0`
	*/
	virtual bool_type test() const = 0;
	template<typename T>
	friend T cast(member* m);

protected:
	virtual bool int64_data(std::int64_t& data) const							 = 0;
	virtual bool double_data(double& data) const								 = 0;
	virtual bool other_data(const std::type_info& type, void*& data)			 = 0;
	virtual bool other_data(const std::type_info& type, const void*& data) const = 0;
};

} // namespace member
} // namespace bia