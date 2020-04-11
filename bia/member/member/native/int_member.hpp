#ifndef BIA_MEMBER_NATIVE_INT_MEMBER_HPP_
#define BIA_MEMBER_NATIVE_INT_MEMBER_HPP_

#include <cstdint>
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
		printf("hi im getting destroyed: %ld\n", _value);
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return _value ? 1 : 0;
	}
	gc::gcable<member> invoke(gc::stack stack, parameter_count_type count) override
	{
		printf("calling int member (value=%ld) with %d parameter\n", _value, (int) count);

		if (count) {
			return static_cast<member*>(stack.at(count - 1).get())->invoke(stack, count - 1);
		}

		return {};
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