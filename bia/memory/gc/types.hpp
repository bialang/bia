#ifndef BIA_MEMORY_GC_TYPES_HPP_
#define BIA_MEMORY_GC_TYPES_HPP_

#include <bia/util/type_traits/is_castable.hpp>
#include <cstddef>
#include <cstdint>
#include <regex>
#include <string>
#include <type_traits>
#include <utility>

namespace bia {
namespace memory {
namespace gc {

template<typename Type>
struct GC_able
{
	static_assert(std::is_pointer<Type>::value, "Type must be a pointer");

	Type pointer;

	GC_able() noexcept = default;
	template<typename Other, typename = typename std::enable_if<std::is_assignable<Type&, Other>::value>::type>
	GC_able(Other&& other) noexcept(std::is_nothrow_assignable<Type&, Other>::value)
	{
		pointer = other;
	}
	bool is_object() const noexcept
	{
		return reinterpret_cast<std::intptr_t>(pointer) & 0x1;
	}
	Type get() noexcept
	{
		return reinterpret_cast<Type>(reinterpret_cast<std::intptr_t>(pointer) & ~std::intptr_t{ 0x3 });
	}
	const Type get() const noexcept
	{
		return const_cast<GC_able*>(this)->get();
	}
	Type operator->() noexcept
	{
		return get();
	}
	const Type operator->() const noexcept
	{
		return get();
	}
	operator Type() noexcept
	{
		return get();
	}
	operator const Type() const noexcept
	{
		return get();
	}
	template<typename Other, typename = typename std::enable_if<
	                           util::type_traits::Is_static_castable<Type, Other>::value>::type>
	operator Other() noexcept
	{
		return static_cast<Other>(get());
	}
	template<typename Other, typename = typename std::enable_if<
	                           util::type_traits::Is_static_castable<Type, Other>::value>::type>
	operator const Other() const noexcept
	{
		static_assert(util::type_traits::Is_static_castable<Type, Other>::value, "cannot cast to type");
		return static_cast<Other>(get());
	}
	bool operator==(std::nullptr_t) const noexcept
	{
		return get() == nullptr;
	}
	bool operator!=(std::nullptr_t) const noexcept
	{
		return get() != nullptr;
	}
};

static_assert(std::is_trivial<GC_able<void*>>::value, "Implementation error: GC_able must be trivial");

class Base
{
public:
	virtual ~Base() = default;
};

template<typename Type>
struct Container : Base
{
	Type value;

	template<typename Other = Type,
	         typename       = typename std::enable_if<std::is_default_constructible<Other>::value>::type>
	Container() noexcept(std::is_nothrow_default_constructible<Other>::value)
	{}
	template<typename Other>
	Container(Other&& other) : value{ std::forward<Other>(other) }
	{}
};

typedef Container<std::string> String;
typedef Container<std::regex> Regex;

} // namespace gc
} // namespace memory
} // namespace bia

#endif
