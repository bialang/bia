#pragma once

#include <cstdint>
#include <gc/object.hpp>

namespace bia {
namespace member {

class member : public bia::gc::object
{
public:
	typedef unsigned int parameter_count_type;
	typedef int operator_type;
	typedef int flag_type;
	typedef int bool_type;

	enum FLAG : flag_type
	{
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
	virtual member* shallow_copy() = 0;
	/*
	 Creates a deep copy of this object. Every child object will be deep copied unlike in shallow_copy().

	 @returns a deep copy
	*/
	virtual member* deep_copy() = 0;

protected:
};

} // namespace member
} // namespace bia