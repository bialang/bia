#include <exception/unknown_encoder_exception.hpp>
#include <gc/gc.hpp>
#include <string/encoding/encoder.hpp>
#include <string/encoding/standard/ascii.hpp>
#include <string/encoding/standard/utf16.hpp>
#include <string/encoding/standard/utf8.hpp>

namespace bia {
namespace string {
namespace encoding {

#define BIA_STRING_ENCODING_BACKEND_NONE
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
standard::ascii ascii_encoder;
standard::utf8 utf8_encoder;
// standard::utf16<false> utf16le_encoder;
// standard::utf16<true> utf16be_encoder;
#endif

encoder* encoder::get_instance(standard_encoding type)
{
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
	switch (type) {
	case standard_encoding::ascii: return &ascii_encoder;
	default: BIA_THROW(exception::unknown_encoder_exception, u"unsupported string encoding");
	}
#endif
}

void encoder::free_instance(encoder* enc)
{
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
	// these instances are static
#endif
}

} // namespace encoding
} // namespace string
} // namespace bia