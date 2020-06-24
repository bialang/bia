#ifndef BIA_MEMBER_FUNCTION_METHOD_HPP_
#define BIA_MEMBER_FUNCTION_METHOD_HPP_

#include "../member.hpp"

#include <bia/log/log.hpp>
#include <type_traits>

namespace bia {
namespace member {
namespace function {

template<typename Class, typename Return, typename... Args>
class method : public member
{
public:
	typedef Return (Class::*function_type)(Args...);

	method(Class& instance, function_type function) noexcept : _instance{ instance }, _function{ function }
	{}
	~method()
	{
		BIA_LOG(DEBUG, "destroying method function: {}", static_cast<void*>(this));
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
		return gc::gc::active_gc()->construct<method>(_instance, _function).template to<member>();
	}
	gc::gcable<member> invoke(parameters_type params) override
	{
		return connector::connect_method(_instance, _function, params);
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
		return false;
	}
	bool as_data(const std::type_info& type, void* output) const override
	{
		return false;
	}
	void gc_mark_children(bool mark) const noexcept override
	{
		_mark(_instance, mark);
	}

protected:
	void register_gcables(gc::gc& gc) const noexcept override
	{}

private:
	Class& _instance;
	function_type _function;

	template<typename T>
	static typename std::enable_if<std::is_base_of<gc::object::base, T>::value>::type _mark(T& ptr, bool mark)
	{
		gc::object::gc_mark(&ptr, mark);
	}
	template<typename T>
	static typename std::enable_if<!std::is_base_of<gc::object::base, T>::value>::type _mark(T& ptr,
	                                                                                         bool mark)
	{}
};

} // namespace function
} // namespace member
} // namespace bia

#endif
