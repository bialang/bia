#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include <bia/gc/stack.hpp>
#include <bia/gc/token.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {

void execute(util::span<const util::byte*> instructions, gc::root& resources);
void execute(util::span<const util::byte*> instructions, gc::root& resources, gc::Stack<std::int32_t>& stack,
             gc::token& token);

} // namespace bvm
} // namespace bia

#endif
