#ifndef BIA_MEMBER_NATIVE_FLOATING_POINT_HPP_
#define BIA_MEMBER_NATIVE_FLOATING_POINT_HPP_

#include "../member.hpp"
#include "detail/operations.hpp"

#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>
#include <cstdint>

namespace bia {
namespace member {
namespace native {

class floating_point : public member
{
public:
	/**
	 * Constructor.
	 *
	 * @param value the initial value
	 */
	floating_point(float_type value) noexcept : _value(value)
	{}
	~floating_point()
	{
		BIA_LOG(DEBUG, "destroying floating point={}: {}", _value, static_cast<void*>(this));
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
		return gc::gc::active_gc()->construct<floating_point>(_value).template to<member>();
	}
	gc::gcable<member> invoke(parameters_type params) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		return {};
		/*return gc::gc::active_gc()
		    ->construct<floating_point>(detail::operation(_value, op, right.as_float()))
		    .template to<member>();*/
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		switch (op) {
		case self_operator::unary_minus:
			return gc::gc::active_gc()->construct<floating_point>(-_value).template to<member>();
		}

		return {};
	}
	member* get(const native::string& name) override
	{
		return nullptr;
	}
	float_type as_float() const noexcept override
	{
		return _value;
	}
	int_type as_int() const noexcept override
	{
		return static_cast<int_type>(_value);
	}
	bool as_data(const std::type_info& type, void* output) override
	{
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		if (type == typeid(float_type*)) {
			*static_cast<const float_type**>(output) = &_value;

			return true;
		}

		return false;
	}
	void gc_mark_children(bool mark) const noexcept override
	{}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{}

private:
	const float_type _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
