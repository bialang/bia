#pragma once

#include <unordered_set>

#include "allocator.hpp"
#include "hasher.hpp"


namespace bia
{
namespace machine
{

class name_manager
{
public:
	/**
	 * Constructor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	[in]	_allocator	Defines the memory allocator.
	*/
	explicit name_manager(allocator * _allocator) noexcept;
	name_manager(const name_manager & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	[in,out]	_rvalue	Defines the object that should be moved.
	*/
	name_manager(name_manager && _rvalue) noexcept;
	~name_manager();
	/**
	 * Returns the name address. This address will be the same for the same name value.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	_name	Defines the name.
	 * @param	_length	Deifnes the length of the name.
	 *
	 * @return	The name address. It's valid until destruction of this name manager. This address is not zero-terminated.
	 *
	 * @throws	See allocator::allocate().
	*/
	const char * get_name_address(const char * _name, size_t _length);
	/**
	 * Returns the format address. This address will be the same for the same format value.
	 *
	 * @since	3.64.127.716
	 * @date	7-Apr-18
	 *
	 * @param	_format	Defines the format.
	 * @param	_length	Deifnes the length of the name.
	 *
	 * @return	The format address. It's valid until destruction of this name manager. This address is in reverse order and not zero-terminated.
	 *
	 * @throws	See allocator::allocate().
	*/
	const char * get_format_address(const char * _format, size_t _length);

private:
	struct string_entry
	{
		const char * _string;
		size_t _length;

		string_entry(const char * _string, size_t _length) noexcept
		{
			this->_string = _string;
			this->_length = _length;
		}
		string_entry(allocator::universal_allocation _allocation) noexcept
		{
			_string = static_cast<const char*>(_allocation.address);
			_length = _allocation.size;
		}
		bool operator==(const string_entry & _right) const noexcept
		{
			return _length == _right._length ? memcmp(_string, _right._string, _length) == 0 : false;
		}
		allocator::universal_allocation get_allocation() const noexcept
		{
			return { const_cast<char*>(_string), _length };
		}
	};

	struct string_hasher
	{
		size_t operator()(const string_entry & _string) const noexcept
		{
			return utility::hasher<size_t>::hash(static_cast<const char*>(_string._string), _string._length);
		}
	};

	/**	Defines the memory allocator.	*/
	allocator * _allocator;
	/**	Defines the index holding all allocated names.	*/
	std::unordered_set<string_entry, string_hasher> _index;
};

}
}