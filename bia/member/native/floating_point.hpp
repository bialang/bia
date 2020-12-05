#ifndef BIA_MEMBER_NATIVE_FLOATING_POINT_HPP_
#define BIA_MEMBER_NATIVE_FLOATING_POINT_HPP_

#include "../member.hpp"
#include "detail/operations.hpp"

#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>
#include <bia/util/type_traits/equals_any.hpp>
#include <cstdint>

namespace bia {
namespace member {
namespace native {

template<typename Type>
class floating_point : public member
{
public:
	static_assert(util::type_traits::equals_any_type<Type, float, double>::value,
	              "floating_point must equal float or double");

	/**
	 * Constructor.
	 *
	 * @param value the initial value
	 */
	floating_point(Type value) noexcept : _value(value)
	{}
	~floating_point()
	{
		BIA_LOG(TRACE, "destroying floating point={}: {}", _value, static_cast<void*>(this));
	}
	flag_type flags() const override
	{
		return flag_floating_point;
	}
	test_type test(test_operator op, const member& right) const override
	{
		if (op == test_operator::self) {
			return _value ? 1 : 0;
		}
		Type rhs{};
		if (!right.as_data(typeid(Type), &rhs)) {
			BIA_THROW(error::code::bad_cast);
		}
		return detail::test_operation(_value, op, rhs);
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<floating_point>(_value);
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		Type rhs{};
		if (!right.as_data(typeid(Type), &rhs)) {
			BIA_THROW(error::code::bad_cast);
		}
		return gc::gc::active_gc()->construct<floating_point>(detail::operation(_value, op, rhs));
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		switch (op) {
		case self_operator::unary_minus: return gc::gc::active_gc()->construct<floating_point>(-_value);
		default: break;
		}

		return {};
	}
	gc::gcable<member> get(const native::string& name) override
	{
		return nullptr;
	}
	bool as_data(const std::type_info& type, void* output) override
	{
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		if (type == typeid(Type*)) {
			*static_cast<const Type**>(output) = &_value;

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
	const Type _value;
};

} // namespace native
} // namespace member
} // namespace bia

#endif
