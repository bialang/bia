#include "tokenizer/token/identifier.hpp"

#include <string/encoding/unicode.hpp>
#include <util/finally.hpp>

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details identifier(std::istream& input, string::encoding::encoder& encoder,
                                     resource_manager& resource_manager)
{
	using namespace string::encoding;

	auto first     = true;
	auto streambuf = resource_manager.start_memory(true);
	auto outenc    = encoder::get_instance(encoder::standard_encoding::utf_8);
	auto free      = util::make_finally([outenc] { encoder::free_instance(outenc); });

	std::ostream output(&streambuf);

	while (true) {
		auto pos = input.tellg();
		auto cp  = encoder.read(input);

		switch (category_of(cp)) {
		case category::Ll:
		case category::Lu:
		case category::Lt:
		case category::Lo:
		case category::Pc:
		case category::Nl: first = false;
		case category::Nd:
		case category::No: {
			// add to output
			if (!first) {
				outenc->put(output, cp);

				break;
			}
		}
		default: {
			// invalid char -> reset
			input.seekg(pos);

			// valid identifier
			if (!first) {
				// zero terminate
				outenc->put(output, 0);
				streambuf.commit_close();
			}

			return { !first };
		}
		}
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia