#include "ascii.hpp"

#include <bia/error/exception.hpp>

using namespace bia::string::encoding::standard;

void ASCII::put(std::ostream& output, code_point_type cp) const
{
	// invalid ascii
	if (cp & ~0x7f) {
		BIA_THROW(error::Code::bad_ascii);
	}
	output.put(static_cast<char>(cp));
}

bia::string::encoding::code_point_type ASCII::read(std::istream& input) const
{
	// no more input
	const auto cp = input.get();
	if (cp == std::istream::traits_type::eof()) {
		input.clear();
		return eof;
	} // invalid ascii
	else if (cp & ~0x7f) {
		BIA_THROW(error::Code::bad_ascii);
	}
	return static_cast<code_point_type>(cp);
}
