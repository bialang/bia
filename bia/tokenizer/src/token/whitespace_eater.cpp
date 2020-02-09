#include "tokenizer/token/whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {

exception::syntax_details eat_whitespaces(std::istream& input, string::encoding::encoder& encoder)
{
	auto eaten = false;

	while (true) {
		auto pos = input.tellg();
		auto cp  = encoder.read(input);

		switch (cp) {
		case ' ':
		case '\t': {
			eaten = true;

			break;
		}
		default: {
			input.seekg(pos);

			return { !eaten };
		}
		}
	}
}

} // namespace token
} // namespace tokenizer
} // namespace bia