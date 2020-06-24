#ifndef BIA_MEMBER_FUNCTION_STATIC_HPP_
#define BIA_MEMBER_FUNCTION_STATIC_HPP_

#include "../member.hpp"

#include <bia/gc/gc.hpp>
#include <bia/log/log.hpp>

namespace bia {
namespace member {
namespace function {

template<typename Return, typename... Args>
class static_ : public member
{
public:
	typedef Return (*function_type)(Args...);

	/**
	 * Constructor.
	 */
	static_(function_type function) noexcept : _function(function)
	{}
	~static_()
	{
		BIA_LOG(DEBUG, "destroying static function: {}", static_cast<void*>(this));
	}
	flag_type flags() const override
	{
		return flag_none;
	}
	test_type test(test_operator op, const member& right) const override
	{
		return 1;
	}
	gc::gcable<member> copy() const override
	{
		return gc::gc::active_gc()->construct<static_>(_function);
	}
	gc::gcable<member> invoke(parameters_type params) override
	{
		return connector::connect_static(_function, params);
	}
	gc::gcable<member> operation(const member& right, infix_operator op) override
	{
		return {};
	}
	gc::gcable<member> self_operation(self_operator op) override
	{
		return {};
	}
	member* get(const native::string& name) override
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
		return static_cast<const static_*>(this)->as_data(type, output);
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		if (type == typeid(function_type)) {
			*static_cast<function_type*>(output) = _function;

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
	function_type _function;
};

} // namespace function
} // namespace member
} // namespace bia

#endif
