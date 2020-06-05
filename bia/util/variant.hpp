#ifndef BIA_UTIL_VARIANT_HPP_
#define BIA_UTIL_VARIANT_HPP_

#include "aggregate.hpp"
#include "type_traits/are_all_copyable.hpp"
#include "type_traits/are_all_moveable.hpp"
#include "type_traits/type_at.hpp"
#include "type_traits/type_index.hpp"

#include <bia/exception/bad_variant_access.hpp>
#include <limits>
#include <type_traits>
#include <utility>


namespace bia {
namespace util {

template<typename... Ts>
class variant
{
public:
	constexpr static std::size_t npos = type_traits::type_index<>::npos;

	template<typename T>
	using index_of = type_traits::type_index<T, Ts...>;

	variant() = default;
	template<
	    typename T,
	    typename = typename std::enable_if<!std::is_same<
	        typename std::remove_cv<typename std::remove_reference<T>::type>::type, variant>::value>::type>
	variant(T&& value)
	{
		emplace<T>(std::forward<T>(value));
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
			_copy<0, Ts...>(copy);
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
			_move<0, Ts...>(std::move(move));
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
			_destroy<0, Ts...>();
		}
	}
	template<std::size_t Index>
	typename type_traits::type_at<Index, Ts...>::type& get()
	{
		return const_cast<typename type_traits::type_at<Index, Ts...>::type&>(
		    const_cast<const variant*>(this)->get<Index>());
	}
	template<std::size_t Index>
	const typename type_traits::type_at<Index, Ts...>::type& get() const
	{
		if (_index == npos) {
			BIA_THROW(exception::bad_variant_access, "accessing empty variant");
		} else if (_index != Index) {
			BIA_THROW(exception::bad_variant_access, "wrong index given");
		}

		return *reinterpret_cast<const typename type_traits::type_at<Index, Ts...>::type*>(&_data);
	}
	template<typename T>
	typename std::enable_if<index_of<T>::value != npos, T&>::type get()
	{
		return const_cast<T&>(const_cast<const variant*>(this)->get<T>());
	}
	template<typename T>
	typename std::enable_if<index_of<T>::value != npos, const T&>::type get() const
	{
		if (_index == npos) {
			BIA_THROW(exception::bad_variant_access, "accessing empty variant");
		} else if (_index != index_of<T>::value) {
			BIA_THROW(exception::bad_variant_access, "wrong type given");
		}

		return *reinterpret_cast<const T*>(&_data);
	}
	template<std::size_t Index, typename... Args>
	typename type_traits::type_at<Index, Ts...>::type& emplace(Args&&... args)
	{
		destroy();

		// initialize
		auto ptr =
		    new (&_data) typename type_traits::type_at<Index, Ts...>::type(std::forward<Args>(args)...);

		_index = Index;

		return *ptr;
	}
	template<typename T, typename... Args>
	typename std::enable_if<index_of<T>::value != npos, T&>::type emplace(Args&&... args)
	{
		destroy();

		// initialize
		auto ptr = new (&_data) T(std::forward<Args>(args)...);

		_index = index_of<T>::value;

		return *ptr;
	}
	std::size_t index() const noexcept
	{
		return _index;
	}
	/*template<typename = typename std::enable_if<type_traits::are_all_copy_assignable<Ts...>::value>::type>
	variant& operator=(const variant& copy)
	{
	    if (copy._index != npos) {
	        _copy<0, Ts...>(copy);
	    }

	    return *this;
	}
	template<typename = typename std::enable_if<type_traits::are_all_move_constructible<Ts...>::value>::type>
	variant& operator=(variant&& move)
	{
	    if (move._index != npos) {
	        _move<0, Ts...>(std::move(move));
	    }

	    return *this;
	}*/

private:
	/** the current value */
	typename std::aligned_storage<max(sizeof(Ts)...), max(alignof(Ts)...)>::type _data;
	/** type information about the current type or npos if no value is stored */
	std::size_t _index = npos;

	template<std::size_t Index, typename T, typename... Vs>
	void _destroy() noexcept
	{
		if (Index == _index) {
			reinterpret_cast<T*>(&_data)->~T();

			_index = npos;
		} else {
			_destroy<Index + 1, Vs...>();
		}
	}
	template<std::size_t Index>
	void _destroy() noexcept
	{}
	template<std::size_t Index, typename T, typename... Vs>
	void _copy(const variant& other)
	{
		if (other._index == Index) {
			destroy();

			new (&_data) T(*reinterpret_cast<const T*>(&other._data));

			_index = other._index;
		} else {
			_copy<Index + 1, Vs...>(other);
		}
	}
	template<std::size_t Index>
	void _copy(const variant& other)
	{}
	template<std::size_t Index, typename T, typename... Vs>
	void _move(variant&& other)
	{
		if (other._index == Index) {
			destroy();

			new (&_data) T(std::move(*reinterpret_cast<T*>(&other._data)));

			_index = other._index;

			other.destroy();
		} else {
			_move<Index + 1, Vs...>(std::move(other));
		}
	}
	template<std::size_t Index>
	void _move(variant&& other)
	{}
};

} // namespace util
} // namespace bia

#endif
