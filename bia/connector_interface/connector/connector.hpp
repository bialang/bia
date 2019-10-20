#pragma once

#include <member/member.hpp>
#include <stack/stack.hpp>

namespace bia {
namespace connector {

typedef member::member::param_count_type param_count_type;

template<typename Return, typename... Args>
member::member* static_connector(Return (*function)(Args...), stack::stack* stack, param_count_type param_count);

template<typename Return, typename Class, typename... Args>
member::member* member_connector(Return (Class::*function)(Args...), Class* instance, stack::stack* stack, param_count_type param_count);

/*template<typename Return, typename Class, typename... Args>
member::member* member_connector(Return (Class::*function)(Args...) const, const Class* instance, stack::stack* stack,
								 param_count_type param_count);*/


} // namespace connector
} // namespace bia