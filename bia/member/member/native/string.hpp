#ifndef BIA_MEMBER_NATIVE_STRING_HPP_
#define BIA_MEMBER_NATIVE_STRING_HPP_

#include "../member.hpp"

#include <gc/gc.hpp>
#include <gc/object/pointer.hpp>
#include <cstring>

namespace bia {
namespace member {
namespace native {

class string : public member
{
public:
	/**
	 * Constructor.
	 *
	 * @param value the string
	 */
	string(gc::object::immutable_pointer<const char> value) noexcept : _value(value)
	{}
	~string()
	{
		printf("bye im getting destroyed: %s, %p\n", _value.get(), this);
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return _value.get()[0] ? 1 : 0;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<string>(_value).template to<member>();
	}
	gc::gcable<member> invoke(gc::stack_view stack, parameter_count_type count) override
	{
		return copy();
	}
	member* get(const native::string& name) override
	{
		return nullptr;
	}
	int compare(const string& other) const noexcept
	{
		return std::strcmp(_value.get(), other._value.get());
	}

protected:
	void gc_mark_children(bool mark) const noexcept override
	{
		gc_mark(_value.get(), mark);
	}

private:
	gc::object::immutable_pointer<const char> _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif