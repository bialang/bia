#ifndef BIA_COMPILER_SYMBOL_MANAGER_HPP_
#define BIA_COMPILER_SYMBOL_MANAGER_HPP_

#include "../type/definition.hpp"
#include "builder.hpp"

#include <bia/resource/view.hpp>
#include <bia/util/gsl.hpp>
#include <bia/util/variant.hpp>
#include <map>
#include <vector>

namespace bia {
namespace compiler {
namespace symbol {

class manager
{
public:
	typedef std::uint16_t index_type;

	enum class domain
	{
		local,
		argument
	};

	manager();
	void open_scope();
	void close_scope();
	builder declare(const resource::view& name);

private:
	friend builder;
	typedef std::map<resource::view, variable> map_type;

	map_type _variables;
	std::map<resource::view, location_type> _declared;
	std::vector<std::vector<map_type::const_iterator>> _scopes;
	std::uint16_t _index = 0;

	void _accept_declared(const resource::view& name, variable var);
	void _decline_declared(const resource::view& name);
};

} // namespace symbol
} // namespace compiler
} // namespace bia

#endif
