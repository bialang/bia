#ifndef BIA_COMPILER_MANAGER_VARIABLE_HPP_
#define BIA_COMPILER_MANAGER_VARIABLE_HPP_

#include <bia/resource/view.hpp>
#include <cstdint>
#include <map>
#include <set>
#include <utility>

namespace bia {
namespace compiler {
namespace manager {

class variable
{
public:
	typedef std::uint16_t index_type;

	/**
	 * Searches for the identifier in the variable index.
	 *
	 * @param identifier the key
	 * @returns a pair of the variable index and whether it was found or not
	 */
	std::pair<index_type, bool> find(const resource::view& identifer) noexcept;
	index_type add(resource::view identifer);
	index_type add_overshadower(resource::view identifer);
	index_type add_tmp();
	index_type latest_index() const;
	void remove_tmp(index_type index);
	void remove_overshadower(const resource::view& identifer);

private:
	std::map<resource::view, index_type> _variables;
	std::map<resource::view, index_type> _overshadower;
	std::set<index_type> _holes;
	index_type _next = 0;
};

} // namespace manager
} // namespace compiler
} // namespace bia

#endif
