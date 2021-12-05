#ifndef BIA_INTERNAL_TYPE_FRAMER_HPP_
#define BIA_INTERNAL_TYPE_FRAMER_HPP_

#include <bia/error/exception.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/gc/types.hpp>
#include <bia/util/algorithm.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/type_traits/is_variant.hpp>
#include <bia/util/variant.hpp>
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
	constexpr static bool requires_gc = false;

	constexpr static std::size_t size() noexcept
	{
		return sizeof(Type);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return alignof(Type);
	}
	static void frame(memory::gc::GC*, util::Span<util::Byte*> buffer, Type value)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(util::is_aligned(buffer.data(), alignment()));
		*reinterpret_cast<Type*>(buffer.data()) = value;
	}
	static Type unframe(util::Span<const util::Byte*> buffer)
	{
		BIA_EXPECTS(buffer.size_bytes() == size());
		BIA_EXPECTS(util::is_aligned(buffer.data(), alignment()));
		return *reinterpret_cast<const Type*>(buffer.data());
	}
};

template<typename Type>
struct Framer<
  Type, typename std::enable_if<!std::is_trivial<typename std::decay<Type>::type>::value &&
                                !util::type_traits::Is_variant<typename std::decay<Type>::type>::value>::type>
{
	constexpr static bool requires_gc = true;
	typedef typename std::decay<Type>::type Value;
	typedef memory::gc::Container<Value> Container;
	typedef memory::gc::GC_able<Container*> Pointer;

	constexpr static std::size_t size() noexcept
	{
		return Framer<Pointer>::size();
	}
	constexpr static std::size_t alignment() noexcept
	{
		return Framer<Pointer>::alignment();
	}
	static void frame(memory::gc::GC* gc, util::Span<util::Byte*> buffer, Value value)
	{
		if (!gc) {
			BIA_THROW(error::Code::gc_required);
		}
		Framer<Pointer>::frame(gc, buffer, gc->create<Container>(std::move(value)));
	}
	static Value& unframe(util::Span<const util::Byte*> buffer)
	{
		return Framer<Pointer>::unframe(buffer)->value;
	}
};

template<typename... Types>
struct Framer<util::Variant<Types...>, void>
{
public:
	constexpr static bool requires_gc = util::any(Framer<Types>::requires_gc...);
	constexpr static std::size_t index_size =
	  util::aligned(Framer<std::size_t>::size(), alignof(std::max_align_t));
	// util::aligned(Framer<std::size_t>::size(), util::max(Framer<Types>::alignment()...));

	constexpr static std::size_t size() noexcept
	{
		return index_size + util::max(Framer<Types>::size()...);
	}
	constexpr static std::size_t alignment() noexcept
	{
		return Framer<std::size_t>::alignment();
	}
	static void frame(memory::gc::GC* gc, util::Span<util::Byte*> buffer, util::Variant<Types...> value)
	{
		BIA_EXPECTS(util::is_aligned(buffer.data(), Framer<std::size_t>::alignment()));
		if (requires_gc && !gc) {
			BIA_THROW(error::Code::gc_required);
		}
		Framer<std::size_t>::frame(gc, buffer.subspan(+0, Framer<std::size_t>::size()), value.index());
		if (value.has_value()) {
			_frame<0, Types...>(gc, buffer.subspan(index_size), value);
		}
	}
	static util::Variant<Types...> unframe(util::Span<const util::Byte*> buffer)
	{
		BIA_EXPECTS(util::is_aligned(buffer.data(), Framer<std::size_t>::alignment()));
		const std::size_t index = Framer<std::size_t>::unframe(buffer.subspan(+0, Framer<std::size_t>::size()));
		if (index != util::npos) {
			return _unframe<0, Types...>(index, buffer.subspan(index_size));
		}
		return {};
	}

private:
	template<std::size_t Index>
	static void _frame(memory::gc::GC* gc, util::Span<util::Byte*> buffer, util::Variant<Types...>& value)
	{}
	template<std::size_t Index, typename Type, typename... Others>
	static void _frame(memory::gc::GC* gc, util::Span<util::Byte*> buffer, util::Variant<Types...>& value)
	{
		if (Index == value.index()) {
			BIA_ASSERT(buffer.size() >= Framer<Type>::size());
			Framer<Type>::frame(gc, buffer.subspan(+0, Framer<Type>::size()), value.template get<Index>());
		} else {
			_frame<Index + 1, Others...>(gc, buffer, value);
		}
	}
	template<std::size_t Index>
	static util::Variant<Types...> _unframe(std::size_t index, util::Span<const util::Byte*> buffer)
	{
		return {};
	}
	template<std::size_t Index, typename Type, typename... Others>
	static util::Variant<Types...> _unframe(std::size_t index, util::Span<const util::Byte*> buffer)
	{
		if (Index == index) {
			BIA_ASSERT(buffer.size() >= Framer<Type>::size());
			BIA_EXPECTS(util::is_aligned(buffer.data(), Framer<Type>::alignment()));
			return Framer<Type>::unframe(buffer.subspan(+0, Framer<Type>::size()));
		} else {
			return _unframe<Index + 1, Others...>(index, buffer);
		}
	}
};

} // namespace type
} // namespace internal
} // namespace bia

#endif
