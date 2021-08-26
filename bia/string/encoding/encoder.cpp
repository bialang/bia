#include "encoder.hpp"

#include "../config.hpp"
#include "standard/ascii.hpp"
#include "standard/utf32.hpp"
#include "standard/utf8.hpp"

#include <bia/error/exception.hpp>

using namespace bia::string::encoding;

#if BIA_STRING_ENCODING_BACKEND_NONE
namespace {

standard::ASCII ascii_encoder;
standard::UTF8 utf8_encoder;
standard::UTF32_host utf32_encoder;
standard::UTF32LE utf32le_encoder;
standard::UTF32BE utf32be_encoder;

} // namespace
#endif

Encoder* bia::string::encoding::get_encoder(Standard encoding)
{
#if BIA_STRING_ENCODING_BACKEND_NONE
	switch (encoding) {
	case Standard::ascii: return &ascii_encoder;
	case Standard::utf_8: return &utf8_encoder;
	case Standard::utf_32: return &utf32_encoder;
	case Standard::utf_32_le: return &utf32le_encoder;
	case Standard::utf_32_be: return &utf32be_encoder;
	// TODO implement other encoders
	case Standard::utf_16:
	case Standard::utf_16_le:
	case Standard::utf_16_be:
	default: BIA_THROW(error::Code::bad_switch_value);
	}
#endif
}

void bia::string::encoding::free_encoder(Encoder* encoder)
{}
