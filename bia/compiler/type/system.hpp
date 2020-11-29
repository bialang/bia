#ifndef BIA_COMPILER_TYPE_SYSTEM_HPP_
#define BIA_COMPILER_TYPE_SYSTEM_HPP_

#include "definition.hpp"

#include <map>
#include <bia/resource/view.hpp>

namespace bia {
namespace compiler {
namespace type {

class system
{
public:

private:
	std::map<resource::view, definition*> _definitions;
};

} // namespace type
} // namespace compiler
} // namespace bia

#endif
