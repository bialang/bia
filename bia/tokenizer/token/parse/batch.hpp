#ifndef BIA_TOKENIZER_TOKEN_PARSE_BATCH_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_BATCH_HPP_

#include "tokens.hpp"
#include "whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

const auto no_batch_call = [] { return true; };

template<typename PreStatement>
inline std::error_code batch(parameter& parameter, PreStatement&& pre_statement)
{
	if (parameter.encoder.read(parameter.input) != '{') {
		return error::code::expected_curly_bracket;
	}

	const auto open_index = parameter.bundle.add({ token::batch{ 0 } });
	const auto run_pre = static_cast<const void*>(&pre_statement) == static_cast<const void*>(&no_batch_call);
	std::size_t count  = 0;

	while (true) {
		eat_whitespaces(parameter);

		const auto old = parameter.backup();

		if (pre_statement()) {
			if (!run_pre) {
				parameter.restore(old);
			}

			if (single_stmt(parameter)) {
				parameter.restore(old);

				break;
			}
		}

		if (const auto err = cmd_end(parameter)) {
			return err;
		}

		++count;
	}

	if (parameter.encoder.read(parameter.input) != '}') {
		return error::code::expected_curly_bracket;
	}

	parameter.bundle.at(open_index).value.get<token::batch>().count = count;

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
