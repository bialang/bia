#ifndef BIA_INTERNAL_TYPE_FRAMER_HPP_
#define BIA_INTERNAL_TYPE_FRAMER_HPP_

#include <bia/memory/gc/gc.hpp>
#include <bia/util/gsl.hpp>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

namespace bia {
namespace internal {
namespace type {

template<typename Type, typename = void>
struct Framer;

template<typename Type>
struct Framer<Type, typename std::enable_if<std::is_trivial<Type>::value>::type>
{
	constexpr static std::size_t size() noexcept
	{
		return sizeof(Type);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(Type);
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, Type value)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(reinterpret_cast<std::intptr_t>(buffer.data()) % alignment() == 0);
		*reinterpret_cast<Type*>(buffer.data()) = value;
	}
	static Type unframe(util::Span<const util::Byte*> buffer)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(reinterpret_cast<std::intptr_t>(buffer.data()) % alignment() == 0);
		return *reinterpret_cast<const Type*>(buffer.data());
	}
};

template<typename Type>
struct Framer<
  Type, typename std::enable_if<std::is_same<typename std::decay<Type>::type, std::string>::value>::type>
{
	constexpr static std::size_t size() noexcept
	{
		return sizeof(memory::gc::GC_able<memory::gc::String*>);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(memory::gc::GC_able<memory::gc::String*>);
	}
	static void frame(memory::gc::GC& gc, util::Span<util::Byte*> buffer, std::string value)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(reinterpret_cast<std::intptr_t>(buffer.data()) % alignment() == 0);
		*reinterpret_cast<memory::gc::GC_able<memory::gc::String*>*>(buffer.data()) =
		  gc.create<memory::gc::String>(std::move(value));
	}
	static const std::string& unframe(util::Span<const util::Byte*> buffer)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(reinterpret_cast<std::intptr_t>(buffer.data()) % alignment() == 0);
		return (*reinterpret_cast<const memory::gc::GC_able<memory::gc::String*>*>(buffer.data()))->string;
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
