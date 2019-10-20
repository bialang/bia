#pragma once

#include "syntax_exception.hpp"

namespace bia {
namespace exception {

class syntax_limitation_exception : public syntax_exception
{
public:
	using syntax_exception::syntax_exception;
};

} // namespace exception
} // namespace bia