#pragma once

#include <string>

namespace bia {
namespace util {

template<typename T>
class cstring_iterator
{
public:
	cstring_iterator(const T* start, const T* end) noexcept
	{
		current   = start;
		this->end = end;
	}
	cstring_iterator(const T* string) : cstring_iterator(string, string + std::char_traits<T>::length(string))
	{}
	bool has_next() const noexcept
	{
		return current < end;
	}
	T next() noexcept
	{
		return *current++;
	}

private:
	const T* current;
	const T* end;
};

} // namespace util
} // namespace bia