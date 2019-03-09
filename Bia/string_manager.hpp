#pragma once

#include <vector>

#include "config.hpp"
#include "allocator.hpp"
#include "share_def.hpp"
#include "string_resource.hpp"


namespace bia
{
namespace machine
{

class string_manager
{
public:
	typedef size_t index_t;
	typedef utility::share<string_resource_t> string_t;

	template<typename Char_type>
	struct index_wrapper
	{
		index_t index;
	};
	template<typename Char_type>
	struct string_wrapper
	{
		const string_t * string;
	};

	typedef index_wrapper<char> utf8_index_t;
	typedef string_wrapper<char> utf8_string_t;

	string_manager() noexcept = default;
	string_manager(const string_manager & _copy) = delete;
	string_manager(string_manager && _move) noexcept = default;
	/**
	 * Destructor.
	 *
	 * @since 3.73.150.816
	 * @date 2-Mar-19
	 *
	 * @throws utility::share::~share().
	*/
	BIA_EXPORT ~string_manager();
	/**
	 * Registers a new string resource.
	 *
	 * @remarks The corresponding active @ref machine_context must be set beforehand. See machine_context::activate_context().
	 *
	 * @since 3.73.150.816
	 * @date 2-Mar-19
	 *
	 * @param _string The string resource. Must be allocated with currently active allocator.
	 *
	 * @throws See utility::share::share().
	*/
	BIA_EXPORT index_t register_string(memory::universal_allocation _string);
	template<typename Char_type>
	string_wrapper<Char_type> string(index_t _index) const
	{
		///TODO: add bound checking

		return { &_strings[_index] };
	}

private:
	std::vector<string_t> _strings;
};

}
}