#ifndef BIA_HPP_
#define BIA_HPP_

#include "detail/engine.hpp"
#include "member/cast.hpp"

namespace bia {

using engine     = detail::engine;
using parameters = connector::parameters;
template<typename T>
using cast = member::cast<T>;

} // namespace bia

#endif
