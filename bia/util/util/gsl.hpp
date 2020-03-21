#ifndef BIA_UTIL_GSL_HPP_
#define BIA_UTIL_GSL_HPP_

#include "contract.hpp"

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename T>
class not_null
{
public:
	static_assert(std::is_assignable<T&, std::nullptr_t>::value, "invalid T");

	template<typename Ty>
	not_null(Ty&& value) : _value(std::forward<Ty>(value))
	{
		BIA_EXPECTS(_value != nullptr);
	}
	template<typename Ty>
	not_null(const not_null<Ty>& other) noexcept : not_null(other.get())
	{}
	not_null(std::nullptr_t) = delete;
	T& get()
	{
		BIA_ENSURES(_value != nullptr);

		return _value;
	}
	operator T&()
	{
		return get();
	}
	T operator->()
	{
		return get();
	}

private:
	T _value;
};

typedef const char* czstring;

template<typename T>
using owner = T;

enum class byte : std::uint8_t
{
};

template<typename T>
class span
{
public:
	typedef T element_type;
	typedef typename std::remove_cv<T>::type value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	typedef pointer iterator;

	span() noexcept
	{
		_data = nullptr;
		_size = 0;
	}
	span(pointer begin, size_type count)
	{
		_data = begin;
		_size = count;
	}
	span(pointer begin, pointer end)
	{
		_data = begin;
		_size = static_cast<size_type>(end - begin);
	}
	span(const span& copy) = default;
	bool empty() const noexcept
	{
		return _size;
	}
	size_type size() const noexcept
	{
		return _size;
	}
	size_type size_bytes() const noexcept
	{
		return _size * sizeof(value_type);
	}
	iterator begin()
	{
		return _data;
	}
	iterator end()
	{
		return _data + _size;
	}
	span subspan(std::size_t offset, std::size_t count)
	{
		BIA_EX

		return { _data + offset, _data + offset + count };
	}
	pointer data() const noexcept
	{
		return _data;
	}
	reference operator[](size_type index) const
	{
		return _data[index];
	}
	span& operator=(const span& copy) = default;

private:
	pointer _data;
	size_type _size;
};

} // namespace util
} // namespace bia

#endif