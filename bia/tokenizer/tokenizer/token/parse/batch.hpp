#ifndef BIA_TOKENIZER_TOKEN_PARSE_BATCH_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_BATCH_HPP_

#include "../parameter.hpp"
#include "expression.hpp"
#include "whitespace_eater.hpp"

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

exception::syntax_details single_stmt(parameter& parameter);
exception::syntax_details cmd_end(parameter& parameter);

const auto no_batch_call = [] { return true; };

template<typename PreStatement>
inline exception::syntax_details batch(parameter& parameter, PreStatement&& pre_statement)
{
	if (parameter.encoder.read(parameter.input) != '{') {
		return { parameter.input.tellg(), "expected '{'" };
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
		return { parameter.input.tellg(), "expected '}'" };
	}

	parameter.bundle.at(open_index).value.get<token::batch>().count = count;

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
