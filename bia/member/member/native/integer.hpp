#ifndef BIA_MEMBER_NATIVE_INTEGER_HPP_
#define BIA_MEMBER_NATIVE_INTEGER_HPP_

#include "../member.hpp"
#include <cstdint>
#include <gc/gc.hpp>

namespace bia {
namespace member {
namespace native {

/**
 * A simple int member capable of holding an int64. This member is always unmutable.
 */
class integer : public member
{
public:
	/**
	 * Constructor.
	 *
	 * @param value the initial value
	 */
	integer(int_type value) noexcept : _value(value)
	{}
	~integer()
	{
		printf("bye im getting destroyed: %ld, %p\n", _value, this);
	}
	flag_type flags() const override
	{
		return flag_numeric;
	}
	test_type test() const override
	{
		return _value ? 1 : 0;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<integer>(_value).template to<member>();
	}
	gc::gcable<member> invoke(gc::stack_view stack, parameter_count_type count) override
	{
		printf("calling int member (value=%ld) with %d parameter\n", _value, (int) count);

		for (parameter_count_type i = 0; i < count; ++i) {
			printf("%d parameter: %ld\n", i, static_cast<integer*>(stack.arg_at(i).get())->_value);
		}

		return gc::gc::active_gc()->construct<integer>(616161).template to<member>();
	}
	member* get(const native::string& name) override
	{
		return nullptr;
	}
	float_type as_float() const noexcept override
	{
		return static_cast<float_type>(_value);
	}
	int_type as_int() const noexcept override
	{
		return _value;
	}
	bool as_data(const std::type_info& type, void* output) override
	{
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		const auto hash = type.hash_code();

		if (hash == typeid(int_type*).hash_code()) {
			*static_cast<const int_type**>(output) = &_value;

			return true;
		}

		return false;
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