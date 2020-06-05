#include "encoding/encoder.hpp"

#include "encoding/standard/ascii.hpp"

#include <bia/exception/implementation_error.hpp>

using namespace bia::string::encoding;

#define BIA_STRING_ENCODING_BACKEND_NONE
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
static standard::ascii ascii_encoder;
#endif

encoder* bia::string::encoding::get_encoder(standard_encoding encoding)
{
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
	switch (encoding) {
	case standard_encoding::ascii: return &ascii_encoder;
	case standard_encoding::utf_8: return &ascii_encoder;
	case standard_encoding::utf_16:
	case standard_encoding::utf_16_le:
	case standard_encoding::utf_16_be:
	case standard_encoding::utf_32:
	case standard_encoding::utf_32_le:
	case standard_encoding::utf_32_be:
	default: BIA_IMPLEMENTATION_ERROR("not implemented");
	}
#endif
}

void bia::string::encoding::free_encoder(encoder* encoder)
{}
