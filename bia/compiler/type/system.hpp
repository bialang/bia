#ifndef BIA_COMPILER_TYPE_SYSTEM_HPP_
#define BIA_COMPILER_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <bia/resource/view.hpp>
#include <map>

namespace bia {
namespace compiler {
namespace type {

class system
{
public:
	system();
	~system();

	definition* get(const resource::view& name);
private:
	std::map<resource::view, definition*> _definitions;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
