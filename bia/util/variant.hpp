#ifndef BIA_UTIL_VARIANT_HPP_
#define BIA_UTIL_VARIANT_HPP_

#include "aggregate.hpp"
#include "type_traits/are_all_copyable.hpp"
#include "type_traits/are_all_moveable.hpp"
#include "type_traits/type_at.hpp"
#include "type_traits/type_index.hpp"

#include <bia/error/exception.hpp>
#include <limits>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename... Types>
class variant
{
public:
	constexpr static std::size_t npos       = type_traits::type_index<>::npos;
	constexpr static std::size_t type_count = sizeof...(Types);

	template<typename Type>
	using index_of = type_traits::type_index<Type, Types...>;

	variant() = default;
	template<
	  typename Type,
	  typename = typename std::enable_if<!std::is_same<
	    typename std::remove_cv<typename std::remove_reference<Type>::type>::type, variant>::value>::type>
	variant(Type&& value)
	{
		emplace<typename std::decay<Type>::type>(std::forward<Type>(value));
	}
	/**
	 * Copy-Constructor. Only available if all variant types are copy constructible.
	 *
	 * @param copy the object to copy
	 * @throw see the copy constructors of the types
	 */
	variant(const variant& copy)
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
	variant(variant&& move)
	{
		if (move._index != npos) {
			_move<0, Types...>(std::move(move));
		}
	}
	~variant()
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
		  const_cast<const variant*>(this)->get<Index>());
	}
	template<std::size_t Index>
	const typename type_traits::type_at<Index, Types...>::type& get() const
	{
		if (_index == npos) {
			BIA_THROW(error::code::empty_variant);
		} else if (_index != Index) {
			BIA_THROW(error::code::bad_variant_index);
		}
		return *reinterpret_cast<const typename type_traits::type_at<Index, Types...>::type*>(&_data);
	}
	template<typename Type>
	typename std::enable_if<index_of<Type>::value != npos, Type&>::type get()
	{
		return const_cast<Type&>(const_cast<const variant*>(this)->get<Type>());
	}
	template<typename Type>
	typename std::enable_if<index_of<Type>::value != npos, const Type&>::type get() const
	{
		if (_index == npos) {
			BIA_THROW(error::code::empty_variant);
		} else if (_index != index_of<Type>::value) {
			BIA_THROW(error::code::bad_variant_index);
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
	bool operator==(std::nullptr_t) const noexcept
	{
		return empty();
	}
	template<typename Type>
	bool operator==(const Type& value) const noexcept
	{
		return has_value(value);
	}
	template<typename Type>
	bool operator!=(const Type& value) const noexcept
	{
		return !has_value(value);
	}
	variant& operator=(const variant& copy)
	{
		if (copy._index != npos) {
			_copy<0, Types...>(copy);
		}
		return *this;
	}
	variant& operator=(variant&& move)
	{
		if (move._index != npos) {
			_move<0, Types...>(std::move(move));
		}
		return *this;
	}

private:
	/// the current value
	typename std::aligned_storage<max(sizeof(Types)...), max(alignof(Types)...)>::type _data;
	/// type information about the current type or npos if no value is stored
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
	void _copy(const variant& other)
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
	void _copy(const variant& other)
	{}
	template<std::size_t Index, typename Type, typename... Others>
	void _move(variant&& other)
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
	void _move(variant&& other)
	{}
};

} // namespace util
} // namespace bia

#endif
