#ifndef BIA_MEMBER_NATIVE_INTEGER_HPP_
#define BIA_MEMBER_NATIVE_INTEGER_HPP_

#include "../member.hpp"
#include "detail/operations.hpp"

#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>
#include <cstdint>
#include <type_traits>

namespace bia {
namespace member {
namespace native {

/**
 * A simple int member capable of holding an int64. This member is always unmutable.
 */
template<typename Type>
class integer : public member
{
public:
	static_assert(std::is_integral<Type>::value && sizeof(Type) <= 8, "integer must be of integral type");

	/**
	 * Constructor.
	 *
	 * @param value the initial value
	 */
	integer(Type value) noexcept : _value(value)
	{}
	~integer()
	{
		BIA_LOG(TRACE, "destroying int={}: {}", _value, static_cast<void*>(this));
	}
	flag_type flags() const override
	{
		return flag_numeric;
	}
	test_type test(test_operator op, const member& right) const override
	{
		if (op == test_operator::self) {
			return _value ? 1 : 0;
		}
		Type rhs{};
		if (!right.as_data(typeid(Type), &rhs)) {
			BIA_THROW(error::Code::bad_cast);
		}
		return detail::test_operation(_value, op, rhs);
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<integer>(_value);
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		Type rhs{};
		if (!right.as_data(typeid(Type), &rhs)) {
			BIA_THROW(error::Code::bad_cast);
		}
		return gc::gc::active_gc()->construct<integer>(detail::operation(_value, op, rhs));
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		switch (op) {
		case self_operator::unary_minus: return gc::gc::active_gc()->construct<integer>(-_value);
		case self_operator::bitwise_not: return gc::gc::active_gc()->construct<integer>(~_value);
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
