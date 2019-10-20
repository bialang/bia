#pragma once

#include "error.hpp"

#define BIA_IMPLEMENTATION_ERROR(msg) BIA_THROW(bia::exception::implementation_error, msg)

namespace bia {
namespace exception {

class implementation_error : public error
{
public:
	using error::error;
};

} // namespace exception
} // namespace bia