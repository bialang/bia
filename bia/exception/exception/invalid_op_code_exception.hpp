#pragma once

#include "exception.hpp"

namespace bia {
namespace exception {

class invalid_op_code_exception : public exception
{
public:
	using exception::exception;
};

} // namespace exception
} // namespace bia