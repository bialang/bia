#pragma once

#include "throwable.hpp"

namespace bia {
namespace exception {

class exception : public throwable
{
public:
	using throwable::throwable;
};

} // namespace exception
} // namespace bia