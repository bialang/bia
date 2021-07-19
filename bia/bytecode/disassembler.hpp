#ifndef BIA_BYTECODE_DISASSEMBLER_HPP_
#define BIA_BYTECODE_DISASSEMBLER_HPP_

#include <ios>

namespace bia {
namespace bytecode {

void disassemble(std::istream& input, std::ostream& output);

}
} // namespace bia

#endif
