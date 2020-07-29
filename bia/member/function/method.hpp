#ifndef BIA_MEMBER_FUNCTION_METHOD_HPP_
#define BIA_MEMBER_FUNCTION_METHOD_HPP_

#include "../member.hpp"

#include <bia/log/log.hpp>
#include <bia/util/type_traits/method_info.hpp>
#include <type_traits>

namespace bia {
namespace member {
namespace function {

template<bool Refer, typename Function>
class method;

template<typename Function>
class method<false, Function> : public member
{
public:
	typedef typename util::type_traits::method_info<Function>::function_type function_type;
	typedef typename util::type_traits::method_info<Function>::class_type class_type;

	method(class_type&& instance, function_type function) noexcept
	    : _instance{ std::move(instance) }, _function{ function }
	{}
	method(const class_type& instance, function_type function) noexcept
	    : _instance{ instance }, _function{ function }
	{}
	~method()
	{
		BIA_LOG(TRACE, "destroying method function: {}", static_cast<void*>(this));
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
		return gc::gc::active_gc()->construct<method>(_instance, _function);
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override
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
	class_type _instance;
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

template<typename Function>
class method<true, Function> : public member
{
public:
	typedef typename util::type_traits::method_info<Function>::function_type function_type;
	typedef typename std::conditional<util::type_traits::method_info<Function>::is_const,
	                                  const typename util::type_traits::method_info<Function>::class_type,
	                                  typename util::type_traits::method_info<Function>::class_type>::type
	    class_type;

	method(class_type& instance, function_type function) noexcept
	    : _instance{ instance }, _function{ function }
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
		return gc::gc::active_gc()->construct<method>(_instance, _function);
	}
	gc::gcable<member> invoke(parameters_type params, invoke_context& context) override
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
	class_type& _instance;
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
