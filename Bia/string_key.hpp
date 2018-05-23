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

	string_key(const char * _string) noexcept : string_key(_string, std::char_traits<char>::length(_string))
	{
	}
	string_key(const char * _string, size_t _length) noexcept
	{
		_string_ptr = _string;
		this->_length = _length;
	}
	string_key(const char * _begin, const char * _end) noexcept : string_key(_begin, _end - _begin)
	{
	}
	bool operator==(const string_key & _right) const noexcept
	{
		if (_string_ptr == _right._string_ptr) {
			return true;
		}

		return _length == _right._length ? !std::char_traits<char>::compare(_string_ptr, _right._string_ptr, _length) : false;
	}
	const char * get_string() const noexcept
	{
		return _string_ptr;
	}
	size_t length() const noexcept
	{
		return _length;
	}

private:
	const char * _string_ptr;
	size_t _length;
};

}
}