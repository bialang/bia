#pragma once

#include <member/member.hpp>

namespace bia {
namespace member {
namespace function {

template<T>
class functor_member;

template<typename Class, typename Return, typename... Args>
class functor_member<Return (Class::*)(Args...)> : public member
{
public:
	typedef Return (Class::*method_type)(Args...);

	functor_member(method_type method, Class* instance, bool gc_collectible) noexcept
	    : method(method), instance(instance), gc_collectible(gc_collectible)
	{}

	virtual member* bind(const std::type_info& type, void* instance, bool gc_collectible) const override
	{
		if (typeid(Class) != type) {
		}

		return gc::gc::active_gc()->construct<functor_member>(method, static_cast<Class*>(instance), gc_collectible);
	}
	virtual member* bind(const std::type_info& type, const void* instance, bool gc_collectible) const override
	{
		BIA_THROW();
	}

protected:
	virtual void gc_mark_children(bool mark) const noexcept override
	{
		if (gc_collectible) {
			gc_mark(instance, mark);
		}
	}

private:
	const method_type method;
	Class* const instance;
	const bool gc_collectible;
};

} // namespace function
} // namespace member
} // namespace bia