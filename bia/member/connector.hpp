#ifndef BIA_MEMBER_CONNECTOR_HPP_
#define BIA_MEMBER_CONNECTOR_HPP_

#include <cstdint>

namespace bia {
namespace member {

class member;

}

namespace gc {

template<typename>
class gcable;
class stack_view;

} // namespace gc
namespace connector {

class parameters;

typedef const parameters& parameters_type;

template<typename Return, typename... Args>
gc::gcable<member::member> connect_static(Return (*function)(Args...), parameters_type params);

template<typename Class, typename Return, typename... Args>
gc::gcable<member::member> connect_method(Class& instance, Return (Class::*function)(Args...),
                                          parameters_type params);

} // namespace connector
} // namespace bia

#endif
