#include "encoder.hpp"

#include "../config.hpp"
#include "standard/ascii.hpp"
#include "standard/utf8.hpp"

#include <bia/error/exception.hpp>

using namespace bia::string::encoding;

#if BIA_STRING_ENCODING_BACKEND_NONE
static standard::ascii ascii_encoder;
static standard::utf8 utf8_encoder;
#endif

encoder* bia::string::encoding::get_encoder(standard_encoding encoding)
{
#if BIA_STRING_ENCODING_BACKEND_NONE
	switch (encoding) {
	case standard_encoding::ascii: return &ascii_encoder;
	case standard_encoding::utf_8: return &utf8_encoder;
	case standard_encoding::utf_16:
	case standard_encoding::utf_16_le:
	case standard_encoding::utf_16_be:
	case standard_encoding::utf_32:
	case standard_encoding::utf_32_le:
	case standard_encoding::utf_32_be:
	default: BIA_THROW(error::code::bad_switch_value);
	}
#endif
}

void bia::string::encoding::free_encoder(encoder* encoder)
{}
