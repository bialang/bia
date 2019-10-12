#pragma once

#include "../member.hpp"

#include <cstdint>

namespace bia {
namespace member {
namespace framework {

/*
 A simple int member capable of holding an int64. This member is always unmutable. If an integer overflow would occur,
 the result will be stored in an big int.
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
		return deep_copy();
	}
	virtual member* deep_copy() override
	{
		return gc::gc::active_gc()->construct<int_member>(*this);
	}
	virtual bool_type test() const override
	{
		return value ? 1 : 0;
	}

protected:
	virtual bool int64_data(std::int64_t& data) const override
	{
		data = value;

		return true;
	}
	virtual bool double_data(double& data) const override
	{
		data = static_cast<double>(value);

		return true;
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
		// has no gc monitored children
	}

private:
	const int_type value;
};

} // namespace framework
} // namespace member
} // namespace bia