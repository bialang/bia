#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "member.hpp"
#include "allocator.hpp"
#include "stl_allocator_wrapper.hpp"
#include "guard.hpp"
#include "exception.hpp"


namespace bia
{
namespace machine
{

/**
 * @brief Holds all known variables.
 *
 * Holds all global variables for the machine context.
 *
 * @see @ref machine_context
*/
class variable_index
{
public:
	/** The value type. */
	typedef memory::allocation<framework::member> value_type;

	/**
	 * Constructor.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @param _allocator The allocator that should be used.
	*/
	explicit variable_index(const std::shared_ptr<memory::allocator> & _allocator) noexcept;
	/**
	 * Adds a member to the global scope.
	 *
	 * @remarks The key address should be created by one @ref string_manager.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @param _key The key.
	 * @param _value The member allocation.
	 *
	 * @throws exception::symbol_error When the key already exists.
	 * @throws See std::unordered_map::emplace().
	 *
	 * @return The inserted member address.
	*/
	framework::member * add(const char * _key, value_type _value);
	/**
	 * Searches for the key and returns the value.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @param _key The key.
	 *
	 * @throws See std::unordered_map::find().
	 *
	 * @return The value associated with the key if it succeeds, otherwise null.
	*/
	framework::member * find(const char * _key);

private:
	static void guard_action(value_type & _value);

	/** The key type of the map. */
	typedef const char* key_type;
	/** The value type of the map. */
	typedef utility::guard<value_type, decltype(&variable_index::guard_action)> mapped_type;
	/** The allocator of the map. */
	typedef memory::stl_allocator_wrapper<std::pair<const key_type, mapped_type>> allocator_type;

	/** The hash map holding all keys and values. */
	std::unordered_map<key_type, mapped_type, std::hash<key_type>, std::equal_to<key_type>, allocator_type> _map;
};

}
}