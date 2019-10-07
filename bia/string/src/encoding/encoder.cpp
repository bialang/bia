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
//standard::utf8 utf8_encoder;
//standard::utf16<false> utf16le_encoder;
//standard::utf16<true> utf16be_encoder;
#endif

string encoder::convert(const std::int8_t* input, std::size_t length)
{
	/*auto& to = get_instance(STANDARD_ENCODING::UTF_16);
	auto buffer =
		static_cast<std::int8_t*>(gc::gc::active_gc()->allocate(to.max_size(from.max_code_points(length) + 1)));
	const auto begin = buffer;
	std::size_t size = 0;
	code_point code_points[32];

	while (length > 0) {
		auto tmp = from.decode(input, length, code_points, 32);

		buffer = to.encode(code_points, static_cast<std::size_t>(tmp - code_points), buffer, 0);
	}*/
	throw;
	// return string(reinterpret_cast<const char_type*>(begin), size);
}

encoder* encoder::get_instance(STANDARD_ENCODING type)
{
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
	switch (type) {
	//case STANDARD_ENCODING::ASCII: return &ascii_encoder;
	//case STANDARD_ENCODING::UTF_8: return &utf8_encoder;
	//case STANDARD_ENCODING::UTF_16_LE: return &utf16le_encoder;
	//case STANDARD_ENCODING::UTF_16_BE: return &utf16be_encoder;
	default: throw exception::unknown_encoder_exception(u"unsupported string encoding");
	}
#endif
}

encoder* encoder::get_instance(string name)
{
#if defined(BIA_STRING_ENCODING_BACKEND_ICU)

#elif defined(BIA_STRING_ENCODING_BACKEND_NONE)
#endif
	throw;
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