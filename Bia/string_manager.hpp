#pragma once

#include <unordered_set>
#include <vector>

#include "config.hpp"
#include "allocator.hpp"
#include "hasher.hpp"


namespace bia
{
namespace machine
{

class string_manager
{
public:
	/** The type of the member name. */
	typedef const char* name_t;

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
	BIA_EXPORT explicit string_manager(memory::allocator * _allocator) noexcept;
	string_manager(const string_manager & _copy) = delete;
	/**
	 * Move-Constructor.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param [in,out] _move Defines the object that should be moved.
	*/
	BIA_EXPORT string_manager(string_manager && _move) noexcept;
	/**
	 * Destructor.
	 *
	 * @since 3.64.127.716
	 * @date 6-May-18
	*/
	BIA_EXPORT ~string_manager() noexcept;
	BIA_EXPORT void register_string(memory::universal_allocation _string);
	/**
	 * Returns the name address. This address will be the same for the same name value.
	 *
	 * @since 3.64.127.716
	 * @date 7-Apr-18
	 *
	 * @param _name Defines the UTF-8 formatted name.
	 * @param _length Deifnes the length of the name.
	 *
	 * @throws See memory::allocator::allocate().
	 *
	 * @return The name address. It's valid until destruction of this name manager. This address is zero-terminated.
	*/
	BIA_EXPORT name_t name_address(const char * _name, size_t _length);
	/**
	 * Returns the name address.
	 *
	 * @since 3.71.149.809
	 * @date 28-Dec-18
	 *
	 * @param _name Defines the UTF-8 formatted name.
	 * @param _length Deifnes the length of the name.
	 *
	 * @return The name address if it exists, otherwise null.
	*/
	BIA_EXPORT name_t name_address_or_null(const char * _name, size_t _length) const noexcept;
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
	BIA_EXPORT const char * format_address(const char * _format, size_t _length);

private:
	struct string_entry
	{
		const char * string;
		size_t length;

		string_entry(const char * _string, size_t _length) noexcept
		{
			this->string = _string;
			this->length = _length;
		}
		string_entry(memory::universal_allocation _allocation) noexcept
		{
			string = static_cast<const char*>(_allocation.first);
			length = _allocation.second;
		}
		bool operator==(const string_entry & _right) const noexcept
		{
			return length == _right.length ? memcmp(string, _right.string, length) == 0 : false;
		}
		memory::universal_allocation allocation() const noexcept
		{
			return { const_cast<char*>(string), length };
		}
	};

	struct string_hasher
	{
		size_t operator()(const string_entry & _string) const noexcept
		{
			return utility::hasher<size_t>::hash(static_cast<const char*>(_string.string), _string.length);
		}
	};

	/** Defines the memory allocator. */
	memory::allocator * _allocator;
	/** Defines the index holding all allocated names. */
	std::unordered_set<string_entry, string_hasher> _index;
	/** The registered string resources. */
	std::vector<memory::universal_allocation> _string_resources;
};

}
}