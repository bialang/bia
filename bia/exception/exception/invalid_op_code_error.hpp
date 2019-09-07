#pragma once

#include "error.hpp"

namespace bia {
namespace exception {

class invalid_op_code_error : public error
{
public:
	using error::error;
};

} // namespace exception
} // namespace bia