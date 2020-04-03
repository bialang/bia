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
	int_member(int_type value) noexcept : value(value)
	{}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return value ? 1 : 0;
	}

protected:
	void gc_mark_children(bool mark) const noexcept override
	{}

private:
	const int_type value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif