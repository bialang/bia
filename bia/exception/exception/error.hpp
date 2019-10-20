#pragma once

#include "throwable.hpp"

namespace bia {
namespace exception
{

class error : public throwable
{
public:
	using throwable::throwable;
};

}
} // namespace bia