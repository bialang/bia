#ifndef BIA_UTIL_GSL_HPP_
#define BIA_UTIL_GSL_HPP_

#include "contract.hpp"
#include "type_traits/is_comparable.hpp"

#include <bia/error/exception.hpp>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>

namespace bia {
namespace util {

template<typename Type>
class Not_null
{
public:
	static_assert(type_traits::Is_equal_comparable<Type, std::nullptr_t>::value,
	              "Type must be null comparable");

	template<typename Other>
	Not_null(Other&& value) : _value(std::forward<Other>(value))
	{
		BIA_EXPECTS(!(_value == nullptr));
	}
	template<typename Other, typename = typename std::enable_if<std::is_assignable<Type, Other>::value>::type>
	Not_null(const Not_null<Other>& other) noexcept : Not_null{ other.get() }
	{}
	Not_null(std::nullptr_t) = delete;
	Type& get()
	{
		BIA_ENSURES(!(_value == nullptr));
		return _value;
	}
	const Type& get() const
	{
		BIA_ENSURES(!(_value == nullptr));
		return _value;
	}
	operator Type&()
	{
		return get();
	}
	operator const Type&() const
	{
		return get();
	}
	Type operator->()
	{
		return get();
	}
	const Type operator->() const
	{
		return get();
	}

private:
	Type _value;
};

typedef const char* Czstring;

template<typename Type>
using owner = Type;

template<typename Type>
using gcable = Type;

#if __cplusplus >= 201703L
typedef std::byte Byte;
#else
enum class Byte : std::uint8_t
{
};
#endif

template<typename To, typename From>
constexpr To narrow_cast(From&& from) noexcept
{
	return static_cast<To>(std::forward<From>(from));
}

template<typename To, typename From>
constexpr To narrow(From from)
{
	return static_cast<From>(narrow_cast<To>(from)) != from ||
	           (std::is_signed<To>::value != std::is_signed<From>::value &&
	            (narrow_cast<To>(from) < To{}) != (from < From{}))
	         ? BIA_THROW(error::Code::bad_narrowing)
	         : narrow_cast<To>(from);
}

constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

template<typename Iterable>
class Span
{
public:
	typedef typename std::iterator_traits<Iterable>::value_type value_type;
	typedef std::size_t size_type;
	typedef typename std::iterator_traits<Iterable>::difference_type difference_type;
	typedef typename std::iterator_traits<Iterable>::pointer pointer;
	typedef typename std::iterator_traits<Iterable>::reference reference;

	Span(std::nullptr_t = nullptr) noexcept
	{
		_data = nullptr;
		_size = 0;
	}
	Span(Iterable begin, size_type count) noexcept
	{
		_data = begin;
		_size = count;
	}
	Span(Iterable begin, Iterable end) noexcept
	{
		_data = begin;
		_size = std::distance(begin, end);
	}
	Span(const Span& copy) noexcept = default;
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
	Iterable begin() const noexcept
	{
		return _data;
	}
	Iterable end() const noexcept
	{
		return _data + _size;
	}
	Span subspan(std::size_t offset, std::size_t count = dynamic_extent) const
	{
		if (count == dynamic_extent) {
			count = _size - offset;
		}
		BIA_EXPECTS(offset + count <= _size);
		return { _data + offset, _data + offset + count };
	}
	Span subspan(Iterable from, std::size_t count = dynamic_extent) const
	{
		return subspan(from - _data, dynamic_extent);
	}
	Span left(Iterable pivot) const
	{
		BIA_EXPECTS(pivot >= begin() && pivot <= end());
		return subspan(+0, pivot - begin());
	}
	Iterable data() const noexcept
	{
		return _data;
	}
	reference front() const
	{
		return at(0);
	}
	reference back() const
	{
		return at(size() - 1);
	}
	reference at(size_type index) const
	{
		if (index >= _size) {
			BIA_THROW(error::Code::out_of_bounds);
		}
		return _data[index];
	}
	reference operator[](size_type index) const noexcept
	{
		return _data[index];
	}
	Span& operator=(const Span& copy) noexcept = default;
	bool operator==(Iterable other) const noexcept
	{
		return _data == other;
	}
	bool operator!=(Iterable other) const noexcept
	{
		return _data != other;
	}

private:
	Iterable _data;
	size_type _size;
};

/// Creates a span from the constant string. The span includes the terminating zero character.
template<std::size_t N>
inline Span<const char*> from_cstring(const char (&string)[N]) noexcept
{
	return { string, N };
}

} // namespace util
} // namespace bia

#endif
