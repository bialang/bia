#ifndef BIA_MEMBER_NATIVE_INT_MEMBER_HPP_
#define BIA_MEMBER_NATIVE_INT_MEMBER_HPP_

#include <cstdint>
#include <gc/gc.hpp>
#include <member/member.hpp>

namespace bia {
namespace member {
namespace native {

/**
 * A simple int member capable of holding an int64. This member is always unmutable.
 */
class int_member : public member
{
public:
	typedef std::int64_t int_type;

	/**
	 * Constructor.
	 *
	 * @param value the initial value
	 */
	int_member(int_type value) noexcept : _value(value)
	{}
	~int_member()
	{
		printf("bye im getting destroyed: %ld, %p\n", _value, this);
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return _value ? 1 : 0;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<int_member>(_value).to<member>();
	}
	gc::gcable<member> invoke(gc::stack stack, parameter_count_type count) override
	{
		printf("calling int member (value=%ld) with %d parameter\n", _value, (int) count);

		for (parameter_count_type i = 0; i < count; ++i) {
			printf("%d parameter: %ld\n", i, static_cast<int_member*>(stack.arg_at(i).get())->_value);
		}

		return gc::gc::active_gc()->construct<int_member>(616161).to<member>();
	}

protected:
	void gc_mark_children(bool mark) const noexcept override
	{}

private:
	const int_type _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif