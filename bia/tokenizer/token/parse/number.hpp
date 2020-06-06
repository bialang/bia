#ifndef BIA_TOKENIZER_TOKEN_PARSE_NUMBER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_NUMBER_HPP_

#include "../parameter.hpp"

#include <bia/exception/syntax_error.hpp>
#include <limits>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details number(parameter& parameter)
{
	token::int_type value = 0;
	auto parsed           = false;

	while (true) {
		const auto pos = parameter.input.tellg();
		const auto cp  = parameter.encoder.read(parameter.input);

		if (cp >= '0' && cp <= '9') {
			const auto val = cp - '0';

			// limit
			if (std::numeric_limits<token::int_type>::max() / 10 < value ||
			    std::numeric_limits<token::int_type>::max() - value * 10 < val) {
				return { pos, "integer overflow" };
			}

			value  = value * 10 + val;
			parsed = true;
		} else {
			if (!parsed) {
				return { pos, "invalid number" };
			}

			parameter.input.seekg(pos);
			parameter.bundle.add(token{ token::int_type{ value } });

			return {};
		}
	}
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
