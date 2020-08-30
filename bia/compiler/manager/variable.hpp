#ifndef BIA_COMPILER_MANAGER_VARIABLE_HPP_
#define BIA_COMPILER_MANAGER_VARIABLE_HPP_

#include <bia/resource/view.hpp>
#include <cstdint>
#include <map>
#include <set>
#include <utility>
#include <vector>

namespace bia {
namespace compiler {
namespace manager {

class variable
{
public:
	typedef std::uint16_t index_type;

	enum class type
	{
		local,
		argument
	};

	typedef std::pair<index_type, type> variable_type;

	/**
	 * Searches for the identifier in the variable index.
	 *
	 * @param identifier the key
	 * @return a pair of the variable index and whether it was found or not
	 */
	std::pair<variable_type, bool> find(const resource::view& identifer) noexcept;
	index_type add(resource::view identifer, type type);
	index_type add_overshadower(resource::view identifer);
	index_type add_tmp();
	variable open_scope();
	void remove_tmp(index_type index);
	void remove_overshadower(const resource::view& identifer);
	const std::vector<std::pair<index_type, index_type>>& bindings() const noexcept;

private:
	std::map<resource::view, variable_type> _variables;
	std::map<resource::view, index_type> _overshadower;
	std::set<index_type> _holes;
	std::vector<std::pair<index_type, index_type>> _bindings;
	variable* _parent = nullptr;
	index_type _next  = 0;
};

} // namespace manager
} // namespace compiler
} // namespace bia

#endif
