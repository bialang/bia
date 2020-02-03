#include "tokenizer/token/identifier.hpp"

#include <string/encoding/unicode.hpp>

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details identifier(std::istream& input, string::encoding::encoder& encoder)
{
	using namespace string::encoding;

	auto first = true;

	while (true) {
		auto c = category_of(input.peek());

		switch (c) {
		case CATEGORY::Ll:
		case CATEGORY::Lu:
		case CATEGORY::Lt:
		case CATEGORY::Lo:
		case CATEGORY::Pc:
		case CATEGORY::Nl: {
			first = false;

			break;
		}
		case CATEGORY::Nd:
		case CATEGORY::No: {
			if (!first) {
				break;
			}
		}
		default: {
			return { !first };
		}
		}

		input.get();
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia