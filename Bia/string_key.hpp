#pragma once

#include <cstdint>
#include <string>

#include "hasher.hpp"


namespace bia
{
namespace utility
{

class string_key
{
public:
	/**
	 * @brief The corresponding hasher to @ref string_key.
	*/
	class hasher
	{
	public:
		size_t operator()(const string_key & _object) const noexcept
		{
			return utility::hasher<size_t>::hash(_object._string_ptr, _object._length);
		}
	};

	string_key(const char * _string);
	string_key(const char * _string, size_t _length);
	string_key(const char * _begin, const char * _end);

private:
	const char * _string_ptr;
	size_t _length;
};

}
}