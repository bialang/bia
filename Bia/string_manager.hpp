#pragma once

#include <vector>

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
	~string_manager();
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
	index_t register_string(memory::universal_allocation _string);
	template<typename Char_type>
	const Char_type * string(index_t _index)
	{
		return nullptr;
	}

private:
	typedef utility::share<string_resource_t> string_t;

	std::vector<string_t> _strings;
};

}
}