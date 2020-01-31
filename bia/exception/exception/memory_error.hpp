#ifndef BIA_EXCEPTION_MEMORY_ERROR_HPP_
#define BIA_EXCEPTION_MEMORY_ERROR_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class memory_error : public bia_error
{
public:
	using bia_error::bia_error;
};

} // namespace exception
} // namespace bia

#endif