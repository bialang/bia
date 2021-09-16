#ifndef BIA_BSL_MODULES_HPP_
#define BIA_BSL_MODULES_HPP_

#include <bia/internal/typed_object.hpp>
#include <functional>

namespace bia {
namespace bsl {

typedef std::function<void(internal::Typed_object&)> Module_definition;

void io(internal::Typed_object& object);
void sys(internal::Typed_object& object);
void os(internal::Typed_object& object);
void math(internal::Typed_object& object);

} // namespace bsl
} // namespace bia

#endif
