#ifndef BIA_BVM_BVM_HPP_
#define BIA_BVM_BVM_HPP_

#include <bia/internal/context.hpp>
#include <bia/memory/gc/gc.hpp>
#include <bia/memory/frame.hpp>
#include <bia/resource/deserialize.hpp>
#include <bia/util/gsl.hpp>

namespace bia {
namespace bvm {

void execute(util::Span<const util::Byte*> instructions, memory::Frame frame,
             const resource::Resources& resources, internal::Context& context);

} // namespace bvm
} // namespace bia

#endif
