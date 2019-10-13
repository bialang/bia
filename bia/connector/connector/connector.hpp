#pragma once

#include <member/member.hpp>
#include <stack/stack.hpp>

namespace bia {
namespace connector {

template<typename Return, typename... Args>
inline Return disguised_call(Return(*function)(Args...))
{
	return function(member::cast<Args>(stack->at<member::member*>(0))...);
}

} // namespace connector
} // namespace bia