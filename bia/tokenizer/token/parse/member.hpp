#ifndef BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_
#define BIA_TOKENIZER_TOKEN_PARSE_MEMBER_HPP_

#include "../parameter.hpp"
#include "identifier.hpp"
#include "parameter_list.hpp"

#include <bia/exception/syntax_error.hpp>

namespace bia {
namespace tokenizer {
namespace token {
namespace parse {

inline exception::syntax_details member(parameter& parameter)
{
	goto gt_begin;

	while (true) {
		{
			const auto pos = parameter.input.tellg();

			if (parameter.encoder.read(parameter.input) != '.') {
				parameter.input.seekg(pos);

				break;
			}
		}

	gt_begin:;
		if (const auto err = identifier(parameter)) {
			return err;
		}

		while (true) {
			const auto old = parameter.backup();

			if (parameter_list(parameter)) {
				parameter.restore(old);

				break;
			}
		}
	}

	return {};
}

} // namespace parse
} // namespace token
} // namespace tokenizer
} // namespace bia

#endif
