#ifndef BIA_UTIL_GSL_HPP_
#define BIA_UTIL_GSL_HPP_

#include "contract.hpp"
#include "type_traits/is_null_comparable.hpp"

#include <cstddef>
#include <cstdint>
#include <exception/bad_variant_access.hpp>
#include <exception/bounds_error.hpp>
#include <limits>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename T>
class not_null
{
public:
	static_assert(type_traits::is_equal_null_comparable<T>::value, "invalid T");

	template<typename Ty>
	not_null(Ty&& value) : _value(std::forward<Ty>(value))
	{
		BIA_EXPECTS(!(_value == nullptr));
	}
	template<typename Ty, typename = typename std::enable_if<std::is_assignable<T, Ty>::value>::type>
	not_null(const not_null<Ty>& other) noexcept : not_null(other.get())
	{}
	not_null(std::nullptr_t) = delete;
	T& get()
	{
		BIA_ENSURES(!(_value == nullptr));

		return _value;
	}
	const T& get() const
	{
		BIA_ENSURES(!(_value == nullptr));

		return _value;
	}
	operator T&()
	{
		return get();
	}
	operator const T&() const
	{
		return get();
	}
	T operator->()
	{
		return get();
	}
	const T operator->() const
	{
		return get();
	}

private:
	T _value;
};

typedef const char* czstring;

template<typename T>
using owner = T;

template<typename T>
using gcable = T;

#if __cplusplus >= 201703L
typedef std::byte byte;
#else
enum class byte : std::uint8_t
{
};
#endif

constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

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

	span(std::nullptr_t = nullptr) noexcept
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
		return !_size;
	}
	size_type size() const noexcept
	{
		return _size;
	}
	size_type size_bytes() const noexcept
	{
		return _size * sizeof(value_type);
	}
	iterator begin() const
	{
		return _data;
	}
	iterator end() const
	{
		return _data + _size;
	}
	span subspan(std::size_t offset, std::size_t count = dynamic_extent) const
	{
		if (count == dynamic_extent) {
			count = _size - offset;
		}
		
		BIA_EXPECTS(offset + count <= _size);

		return { _data + offset, _data + offset + count };
	}
	pointer data() const noexcept
	{
		return _data;
	}
	reference at(size_type index) const
	{
		if (index >= _size) {
			BIA_THROW(exception::bounds_error, "out of bounds");
		}

		return _data[index];
	}
	reference operator[](size_type index) const
	{
		return _data[index];
	}
	span& operator=(const span& copy) = default;
	bool operator==(pointer other) const noexcept
	{
		return _data == other;
	}
	bool operator!=(pointer other) const noexcept
	{
		return _data != other;
	}

private:
	pointer _data;
	size_type _size;
};

} // namespace util
} // namespace bia

#endif