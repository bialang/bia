#pragma once

#include "../member.hpp"

#include <string/string.hpp>
#include <gc/gc.hpp>

namespace bia
{
namespace member
{
namespace framework
{

/*
 A member holding a single gc collected string. This member is always unmutable.
*/
class string_member : public member
{
public:
	string_member(string::string str) : str(str)
	{}
	virtual flag_type flags() const override
	{
		return 0;
	}
	virtual member* shallow_copy() override
	{
		return gc::gc::active_gc()->construct<string_member>(*this);
	}
	virtual member* deep_copy() override
	{
		return shallow_copy();
	}

protected:
	virtual void gc_mark_children(bool mark) const noexcept
	{
		// mark string
		gc_mark(str.get_gc_pointer(), mark);
	}

private:
	string::string str;
};

}
}
}