#pragma once

#include <cstring>

#include <gc/gc.hpp>

#include "member.hpp"


namespace bia
{
namespace bvm
{
namespace framework
{

class string_member : public member
{
public:
	string_member(const char16_t* string, std::size_t length, bool constant = false) : string(gc::gc::active_gc()->allocate((length + 1) * sizeof(char16_t)))
	{
		std::memcpy(this->string.get(), string, length * sizeof(char16_t));

		// null terminate
		static_cast<char16_t*>(this->string.get())[length] = 0;
	}
	string_member(const string_member& copy) : constant(false)
	{
		string = gc::gc::active_gc()->allocate()
	}
	virtual member* shallow_copy() override
	{
		return gc::gc::active_gc()->construct<string_member>(*this);
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
		// mark string
		gc_mark(string, mark);
	}

private:
	/* a null terminated UTF-16 encoded string */
	gc::object_ptr string;
	/* the count of unicode units */
	std::size_t length;
	const bool constant;
};

}
}
}