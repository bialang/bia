#ifndef BIA_COMPILER_ELVE_PRESENT_HPP_
#define BIA_COMPILER_ELVE_PRESENT_HPP_

#include "../variable_manager.hpp"

#include <bytecode/writer/instruction.hpp>
#include <resource/serializer.hpp>

namespace bia {
namespace compiler {
namespace elve {

struct present
{
	variable_manager& variable_manager;
	bytecode::writer::instruction& writer;
	resource::serializer& resources;
};

} // namespace elve
} // namespace compiler
} // namespace bia

#endif