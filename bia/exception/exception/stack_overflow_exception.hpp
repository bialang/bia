#pragma once

#include "bvm_exception.hpp"

namespace bia {
namespace exception {

class stack_overflow_exception : public bvm_exception
{
public:
	using bvm_exception::bvm_exception;
};

} // namespace exception
} // namespace bia