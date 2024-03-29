#ifndef BIA_UTIL_VARIANT_HPP_
#define BIA_UTIL_VARIANT_HPP_

#include "algorithm.hpp"
#include "config.hpp"
#include "type_traits/are_all_copyable.hpp"
#include "type_traits/are_all_moveable.hpp"
#include "type_traits/equals_any.hpp"
#include "type_traits/multi_comparable.hpp"
#include "type_traits/type_at.hpp"
#include "type_traits/type_index.hpp"
#include "type_traits/type_select.hpp"

#include <bia/error/exception.hpp>
#include <limits>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename... Types>
class Variant
{
public:
	constexpr static std::size_t type_count = sizeof...(Types);
	static_assert(type_count > 0, "Variant must have at least one type");

	template<typename Type>
	using index_of = type_traits::type_index<Type, Types...>;

	Variant() = default;
	template<typename Type, typename = typename std::enable_if<util::type_traits::equals_any_type<
	                          typename std::decay<Type>::type, Types...>::value>::type>
	Variant(Type&& value)
	{
		emplace<typename std::decay<Type>::type>(std::forward<Type>(value));
	}
	/**
	 * Copy-Constructor. Only available if all variant types are copy constructible.
	 *
	 * @param copy the object to copy
	 * @throw see the copy constructors of the types
	 */
	Variant(const Variant& copy)
	{
		if (copy._index != npos) {
			_copy<0, Types...>(copy);
		}
	}
	/**
	 * Move-Constructor. Only available if all variant types are move constructible.
	 *
	 * @param[in,out] move the object to move
	 * @throw see the move constructors of the types
	 */
	Variant(Variant&& move)
	{
		if (move._index != npos) {
			_move<0, Types...>(std::move(move));
		}
	}
	~Variant() noexcept
	{
		destroy();
	}
	/**
	 * Destroys the content of this variant.
	 *
	 * @post `index() == npos`
	 */
	void destroy() noexcept
	{
		if (_index != npos) {
			_destroy<0, Types...>();
		}
	}
	template<std::size_t Index>
	typename type_traits::type_at<Index, Types...>::type& get()
	{
		return const_cast<typename type_traits::type_at<Index, Types...>::type&>(
		  const_cast<const Variant*>(this)->get<Index>());
	}
	template<std::size_t Index>
	const typename type_traits::type_at<Index, Types...>::type& get() const
	{
		if (_index == npos) {
			BIA_THROW(error::Code::empty_variant);
		} else if (_index != Index) {
			BIA_THROW(error::Code::bad_variant_index);
		}
		return *reinterpret_cast<const typename type_traits::type_at<Index, Types...>::type*>(&_data);
	}
	template<typename Type>
	typename std::enable_if<index_of<Type>::value != npos, Type&>::type get()
	{
		return const_cast<Type&>(const_cast<const Variant*>(this)->get<Type>());
	}
	template<typename Type>
	typename std::enable_if<index_of<Type>::value != npos, const Type&>::type get() const
	{
		if (_index == npos) {
			BIA_THROW(error::Code::empty_variant);
		} else if (_index != index_of<Type>::value) {
			BIA_THROW(error::Code::bad_variant_index);
		}
		return *reinterpret_cast<const Type*>(&_data);
	}
	template<std::size_t Index, typename... Args>
	typename type_traits::type_at<Index, Types...>::type& emplace(Args&&... args)
	{
		destroy();
		const auto ptr =
		  new (&_data) typename type_traits::type_at<Index, Types...>::type{ std::forward<Args>(args)... };
		_index = Index;
		return *ptr;
	}
	template<typename Type, typename... Args>
	typename std::enable_if<index_of<Type>::value != npos, Type&>::type emplace(Args&&... args)
	{
		return emplace<index_of<Type>::value>(std::forward<Args>(args)...);
	}
	std::size_t index() const noexcept
	{
		return _index;
	}
	template<typename Type>
	bool is_type() const noexcept
	{
		static_assert(index_of<Type>::value != npos, "Type is not in variant");
		return _index == index_of<Type>::value;
	}
	template<typename Type>
	bool has_value(const Type& value) const noexcept
	{
		return is_type<Type>() && get<Type>() == value;
	}
	bool empty() const noexcept
	{
		return _index == npos;
	}
	template<typename Type>
	bool operator==(Type&& value) const noexcept
	{
		using Info = type_traits::Multi_equal_comparable<Type, Types...>;
		static_assert(Info::indices.size != 0, "No equal comparable operator in type set");
		static_assert(Info::indices.size < 2, "Type set has two compatible operators");
		using Selected =
		  typename decltype(type_traits::Type_select<Info::indices.first, 1, Types...>::selected)::First;
		return is_type<Selected>() && get<Selected>() == std::forward<Type>(value);
	}
	template<typename Type>
	bool operator!=(Type&& value) const noexcept
	{
		using Info = type_traits::Multi_unequal_comparable<Type, Types...>;
		static_assert(Info::indices.size != 0, "No equal comparable operator in type set");
		static_assert(Info::indices.size < 2, "Type set has two compatible operators");
		using Selected =
		  typename decltype(type_traits::Type_select<Info::indices.first, 1, Types...>::selected)::First;
		return !is_type<Selected>() || get<Selected>() != std::forward<Type>(value);
	}
	Variant& operator=(const Variant& copy)
	{
		if (copy._index != npos) {
			_copy<0, Types...>(copy);
		}
		return *this;
	}
	Variant& operator=(Variant&& move)
	{
		if (move._index != npos) {
			_move<0, Types...>(std::move(move));
		}
		return *this;
	}

private:
	/// The current value.
	typename std::aligned_storage<max(sizeof(Types)...), max(alignof(Types)...)>::type _data;
	/// Type information about the current type or npos if no value is stored.
	std::size_t _index = npos;

	template<std::size_t Index, typename Type, typename... Others>
	void _destroy() noexcept
	{
		if (Index == _index) {
			reinterpret_cast<Type*>(&_data)->~Type();
			_index = npos;
		} else {
			_destroy<Index + 1, Others...>();
		}
	}
	template<std::size_t Index>
	void _destroy() noexcept
	{}
	template<std::size_t Index, typename Type, typename... Others>
	void _copy(const Variant& other)
	{
		if (other._index == Index) {
			destroy();
			new (&_data) Type{ *reinterpret_cast<const Type*>(&other._data) };
			_index = other._index;
		} else {
			_copy<Index + 1, Others...>(other);
		}
	}
	template<std::size_t Index>
	void _copy(const Variant& other)
	{}
	template<std::size_t Index, typename Type, typename... Others>
	void _move(Variant&& other)
	{
		if (other._index == Index) {
			destroy();
			new (&_data) Type{ std::move(*reinterpret_cast<Type*>(&other._data)) };
			_index = other._index;
			other.destroy();
		} else {
			_move<Index + 1, Others...>(std::move(other));
		}
	}
	template<std::size_t Index>
	void _move(Variant&& other)
	{}
};

} // namespace util
} // namespace bia

#endif
