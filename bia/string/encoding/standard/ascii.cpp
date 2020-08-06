#include "ascii.hpp"

#include <bia/exception/invalid_code_point.hpp>

using namespace bia::string::encoding::standard;

void ascii::put(std::ostream& output, code_point_type cp) const
{
	// invalid ascii
	if (cp & ~0x7f) {
		BIA_THROW(exception::invalid_code_point, "code point outside of ASCII range");
	}

	output.put(static_cast<char>(cp));
}

bia::string::encoding::code_point_type ascii::read(std::istream& input) const
{
	const auto cp = input.get();

	// no more input
	if (cp == std::istream::traits_type::eof()) {
		input.clear();

		return eof;
	}

	// invalid ascii
	if (cp & ~0x7f) {
		BIA_THROW(exception::invalid_code_point, "code point outside of ASCII range");
	}

	return static_cast<code_point_type>(cp);
}
