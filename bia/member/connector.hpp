#ifndef BIA_CONNECTOR_INTERFACE_CONNECTOR_HPP_
#define BIA_CONNECTOR_INTERFACE_CONNECTOR_HPP_

#include "member.hpp"

#include <cstdint>

namespace bia {
namespace gc {

template<typename>
class gcable;
class stack_view;

} // namespace gc
namespace connector {

template<typename Return, typename... Args>
gc::gcable<member::member> connect_static(Return (*function)(Args...), gc::stack_view& stack,
                                          std::size_t parameter_count);

} // namespace connector
} // namespace bia

#endif
