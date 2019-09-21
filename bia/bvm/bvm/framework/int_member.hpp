#pragma once

#include "member.hpp"

#include <external/big_int.hpp>
#include <gc/gc.hpp>

namespace bia {
namespace bvm {
namespace framework {

class int_member : public member
{
public:
	int_member(intmax_t value, bool constant = false)
		: integ(value), constant(constant)
	{}
	int_member(const char* value, int base, bool constant = false)
		: integ(value, base), constant(constant)
	{}
	int_member(const int_member& copy) : integ(copy.integ), constant(false)
	{}
	virtual member* shallow_copy() override
	{
		return gc::gc::active_gc()->construct<int_member>(*this);
	}
	virtual member* deep_copy() override
	{
		return shallow_copy();
	}
	virtual member* clone() override
	{
		return constant ? this : shallow_copy();
	}

protected:
	virtual void gc_mark_children(bool mark) const noexcept
	{
		// has no gc monitored children
	}

private:
	constexpr static auto min_bits = 64;

	external::big_int integ;
	const bool constant;
};

} // namespace framework
} // namespace bvm
} // namespace bia