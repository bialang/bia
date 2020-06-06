#ifndef BIA_EXCEPTION_IMPORT_HPP_
#define BIA_EXCEPTION_IMPORT_HPP_

#include "bia_error.hpp"

namespace bia {
namespace exception {

class import : public bia_error
{
public:
	using bia_error::bia_error;
	
	const char* name() const noexcept override
	{
		return "import";
	}
};

} // namespace exception
} // namespace bia

#endif