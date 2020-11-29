#ifndef BIA_COMPILER_VARIABLE_MANAGER_HPP_
#define BIA_COMPILER_VARIABLE_MANAGER_HPP_

#include "type/definition.hpp"

#include <bia/resource/view.hpp>

namespace bia {
namespace compiler {

class variable_manager
{
public:
	typedef std::uint16_t index_type;

	enum class domain
	{
		local,
		argument
	};

	struct variable
	{
		domain domain;
		type::definition* definition;
	};

private:
//	std::map<resource::view, variable> _variables;
};

} // namespace compiler
} // namespace bia

#endif
