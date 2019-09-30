#pragma once

#include "../member.hpp"

#include <cstdint>

namespace bia {
namespace member {
namespace framework {

/*
 A simple int member capable of holding an int64. This member is always unmutable. If an integer overflow would occur, the result will be stored in an big int.
*/
class int_member : public member
{
public:
	typedef std::int64_t int_type;

	int_member(int_type value) : value(value)
	{}
	virtual flag_type flags() const override
	{
		return 0;
	}
	virtual member* shallow_copy() override
	{
		return gc::gc::active_gc()->construct<int_member>(*this);
	}
	virtual member* deep_copy() override
	{
		return shallow_copy();
	}

protected:
	virtual void gc_mark_children(bool mark) const noexcept
	{
		// has no gc monitored children
	}

private:
	int_type value;
};

} // namespace framework
} // namespace bvm
} // namespace bia