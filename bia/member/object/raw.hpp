#ifndef BIA_MEMBER_OBJECT_RAW_HPP_
#define BIA_MEMBER_OBJECT_RAW_HPP_

#include "../member.hpp"

#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>
#include <bia/util/gsl.hpp>
#include <cstring>
#include <utility>

namespace bia {
namespace member {
namespace object {

template<typename Type>
class raw : public member
{
public:
	template<typename T>
	raw(T&& value) noexcept : _value{ std::forward<T>(value) }
	{}
	~raw()
	{}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test() const override
	{
		return false;
	}
	gc::gcable<member> copy() const override
	{
		return {};
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override
	{
		return {};
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		return {};
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		return {};
	}
	gc::gcable<member> get(const native::string& name) override
	{
		return nullptr;
	}
	float_type as_float() const noexcept override
	{
		return {};
	}
	int_type as_int() const noexcept override
	{
		return {};
	}
	bool as_data(const std::type_info& type, void* output) override
	{
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		if (type == typeid(Type*)) {
			*static_cast<Type**>(output) = &_value;

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
	Type _value;
};

} // namespace object
} // namespace member
} // namespace bia

#endif
