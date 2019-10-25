#pragma once

#include <gc/gc.hpp>
#include <member/member.hpp>
#include <string/string.hpp>

namespace bia {
namespace member {
namespace native {

/*
 A member holding a single gc collected string. This member is always unmutable. Copying the string doesn't copy the
 underlying string.
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
	virtual member* shallow_copy() const override
	{
		return deep_copy();
	}
	virtual member* deep_copy() const override
	{
		return gc::gc::active_gc()->construct<string_member>(*this);
	}
	virtual bool_type test() const override
	{
		return str.length() ? 1 : 0;
	}

protected:
	virtual bool int64_data(std::int64_t& data) const override
	{
		return false;
	}
	virtual bool double_data(double& data) const override
	{
		return false;
	}
	virtual bool other_data(const std::type_info& type, void*& data) override
	{
		return false;
	}
	virtual bool other_data(const std::type_info& type, const void*& data) const override
	{
		return false;
	}
	virtual void gc_mark_children(bool mark) const noexcept
	{
		// mark string
		gc_mark(str.get_gc_pointer(), mark);
	}

private:
	string::string str;
};

} // namespace framework
} // namespace member
} // namespace bia