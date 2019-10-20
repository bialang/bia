#pragma once

#include "exception.hpp"

namespace bia {
namespace exception {

class nullpointer_exception : public exception
{
public:
	using exception::exception;
};

} // namespace exception
} // namespace bia