#ifndef BIA_COMPILER_VARIABLE_MANAGER_HPP_
#define BIA_COMPILER_VARIABLE_MANAGER_HPP_

#include <gc/memory/view.hpp>
#include <map>
#include <utility>
#include <vector>

namespace bia {
namespace compiler {

class variable_manager
{
public:
	typedef std::uint32_t index_type;
	typedef std::uint32_t scope_index_type;

	/**
	 * Returns the index of the scope and the variable. If the variable does not yet exist, it will be created
	 * on the newest stack.
	 *
	 * @pre at least one active scope
	 *
	 * @param identifier the name of the variable
	 * @returns the index of the scope and the variable
	 */
	std::pair<scope_index_type, index_type> index_of(gc::memory::view identifier);
	/**
	 * Returns the index of the current scope.
	 *
	 * @pre at least one active scope
	 *
	 * @returns the scope index
	 */
	scope_index_type current_scope() const;
	void open_scope();
	void close_scope();

private:
	struct scope
	{
		std::map<gc::memory::view, index_type> variables;
		index_type index = 0;
	};

	std::vector<scope> _scopes;
};

} // namespace compiler
} // namespace bia

#endif