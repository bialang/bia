#ifndef BIA_ASSEMBLER_DISASSEMBLER_HPP_
#define BIA_ASSEMBLER_DISASSEMBLER_HPP_

#include <bia/gc/root.hpp>
#include <bia/util/gsl.hpp>
#include <ostream>

namespace bia {
namespace assembler {

void disassemble(util::span<const util::byte*> instructions, gc::root& resources, std::ostream& output);

} // namespace assembler
} // namespace bia

#endif
