#pragma once

#include <unordered_set>

#include "allocator.hpp"
#include "hasher.hpp"


namespace bia
{
namespace machine
{

class string_manager
{
public:
	/**
	 * Constructor.
	 *
	 * @remarks The allocator must be valid during the lifetime of this object. It will not be released at the end of the name_managers lifetime.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in] _allocator Defines the memory allocator.
	*/
	explicit string_manager(memory::allocator * _allocator) noexcept;
	string_manager(const string_manager & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in,out] _rvalue Defines the object that should be moved.
	*/
	string_manager(string_manager && _rvalue) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	*/
	~string_manager() noexcept;
	/**
	 * Returns the name address. This address will be the same for the same name value.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _name Defines the name.
	 * @param _length Deifnes the length of the name.
	 *
	 * @throws See memory::allocator::allocate().
	 *
	 * @return The name address. It's valid until destruction of this name manager. This address is not zero-terminated.
	*/
	const char * name_address(const char * _name, size_t _length);
	/**
	 * Returns the format address. This address will be the same for the same format value.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _format Defines the format.
	 * @param _length Deifnes the length of the name.
	 *
	 * @throws See memory::allocator::allocate().
	 *
	 * @return The format address. It's valid until destruction of this name manager. This address is in reverse order and not zero-terminated.
	*/
	const char * format_address(const char * _format, size_t _length);

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
		string_entry(memory::allocator::universal_allocation _allocation) noexcept
		{
			_string = static_cast<const char*>(_allocation.first);
			_length = _allocation.second;
		}
		bool operator==(const string_entry & _right) const noexcept
		{
			return _length == _right._length ? memcmp(_string, _right._string, _length) == 0 : false;
		}
		memory::allocator::universal_allocation get_allocation() const noexcept
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

	/** Defines the memory allocator. */
	memory::allocator * _allocator;
	/** Defines the index holding all allocated names. */
	std::unordered_set<string_entry, string_hasher> _index;
};

}
}