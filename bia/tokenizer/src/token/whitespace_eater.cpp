#include "tokenizer/token/whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details eat_whitespaces(std::istream& input, string::encoding::encoder& encoder)
{
	auto eaten = false;

	while (true) {
		auto c = input.peek();

		switch (c) {
		case ' ':
		case '\t': {
			input.get();

			eaten = true;

			break;
		}
		default: return { !eaten };
		}
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia