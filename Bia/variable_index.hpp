#pragma once

#include <unordered_map>
#include <memory>

#include "string_key.hpp"
#include "hasher.hpp"
#include "member.hpp"
#include "allocator.hpp"
#include "stl_allocator_wrapper.hpp"


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
	/**
	 * Constructor.
	 *
	 * @since 3.64.131.725
	 * @date 19-May-18
	 *
	 * @param _allocator The allocator that should be used.
	*/
	explicit variable_index(const std::shared_ptr<memory::allocator> & _allocator) noexcept;
	framework::member * add(utility::string_key _key, memory::allocator::allocation<framework::member> _value);
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
	framework::member * find(utility::string_key _key);

private:
	typedef utility::string_key key_type;
	typedef std::unique_ptr<framework::member> value_type;
	typedef memory::stl_allocator_wrapper<std::pair<const key_type, value_type>> allocator_type;

	/** The hash map holding all keys and values. */
	std::unordered_map<key_type, value_type, utility::string_key::hasher, std::equal_to<utility::string_key>, allocator_type> _map;
};

}
}