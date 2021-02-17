#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include <bia/memory/stack.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {

void execute(util::Span<const util::Byte*> instructions, memory::Stack& stack,
             const resource::Resources& resources);

} // namespace bvm
} // namespace bia

#endif
