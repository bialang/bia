#ifndef BIA_COMPILER_VARIABLE_MANAGER_HPP_
#define BIA_COMPILER_VARIABLE_MANAGER_HPP_

#include <map>
#include <bia/resource/view.hpp>
#include <utility>
#include <vector>

namespace bia {
namespace compiler {

class variable_manager
{
public:
	typedef std::uint16_t index_type;
	typedef std::uint16_t scope_index_type;

	struct variable
	{
		scope_index_type scope_id;
		index_type id;
	};

	/**
	 * Returns the index of the scope and the variable.
	 *
	 * @param identifier the name of the variable
	 * @returns the index of the variable and `true` if it exists, otherwise `{ *unspecified*, false }`
	 */
	std::pair<variable, bool> index_of(const resource::view& identifier);
	variable add(const resource::view& identifier);
	variable add_tmp();
	variable latest_variable() const;
	void remove_tmp();
	void open_scope();
	void close_scope();

private:
	struct scope
	{
		std::map<resource::view, index_type> variables;
		index_type index = 0;
	};

	std::vector<scope> _scopes;
};

} // namespace compiler
} // namespace bia

#endif
