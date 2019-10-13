#pragma once

#include "exception.hpp"

namespace bia {
namespace exception {

class interrupt_exception : public exception
{
public:
	using exception::exception;
};

} // namespace exception
} // namespace bia