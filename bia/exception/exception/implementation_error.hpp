#pragma once

#include "error.hpp"

#define BIA_IMPLEMENTATION_ERROR(msg) throw bia::exception::implementation_error(msg, __FILE__, __LINE__)

namespace bia {
namespace exception {

class implementation_error : public error
{
public:
	using error::error;
	implementation_error(const char16_t* message, const char* file, int line) : error(message)
	{
		this->file = file;
		this->line = line;
	}

private:
	const char* file;
	int line;
};

} // namespace exception
} // namespace bia